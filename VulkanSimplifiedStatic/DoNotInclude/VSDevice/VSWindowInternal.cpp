#include "VSDeviceNIpch.h"
#include "VSWindowInternal.h"

#include "../../Include/VSDevice/VSWindowCreationData.h"
#include "../../Include/VSDevice/VSSwapchainCreationData.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"

#include "VSDeviceCoreInternal.h"

#include "../../Include/VSMain/EventHandler/SdlWindowEventData.h"

#include "../VSMain/EventHandler/SdlEventHandlerInternal.h"

namespace VulkanSimplifiedInternal
{
	WindowInternal::WindowInternal(SdlEventHandlerInternal& eventHandler, DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
		const VulkanSimplified::WindowCreationData& creationData) : _eventHandler(eventHandler), _core(core)
	{
		_instance = instance;
		_physicalDevice = physicalDevice;
		_device = device;

		_hidden = false;
		_minimized = false;
		_quit = false;
		_bpadding = false;

		_window = nullptr;
		_windowTitle = creationData.windowTitle;

		_surface = VK_NULL_HANDLE;
		_surfaceCapabilities = {};

		_presentMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
		_format = VK_FORMAT_MAX_ENUM;
		_swapchainFlags = VK_SWAPCHAIN_CREATE_FLAG_BITS_MAX_ENUM_KHR;
		_imageAmount = 0;

		_swapchain = VK_NULL_HANDLE;

		Uint32 flags = SDL_WINDOW_VULKAN;

		switch (creationData.settings)
		{
		case VulkanSimplified::WindowSettings::STANDARD:
			break;
		case VulkanSimplified::WindowSettings::RESIZABLE:
			flags |= SDL_WINDOW_RESIZABLE;
			break;
		case VulkanSimplified::WindowSettings::BORDERLESS:
			flags |= SDL_WINDOW_BORDERLESS;
			break;
		case VulkanSimplified::WindowSettings::FULLSCREEN_NONEXCLUSIVE:
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;
		default:
			throw std::runtime_error("WindowInternal::WindowInternal Error: Erroneous window creation settings!");
		}

		ratio = static_cast<double>(std::min(creationData.width, creationData.height)) / static_cast<double>(std::max(creationData.width, creationData.height));

		_window = SDL_CreateWindow(_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(creationData.width), static_cast<int>(creationData.height),
			flags);

		if (_window == nullptr)
			throw std::runtime_error(SDL_GetError());

		_windowID = SDL_GetWindowID(_window);

		if (_windowID == 0)
			throw std::runtime_error(SDL_GetError());

		if (SDL_Vulkan_CreateSurface(_window, _instance, &_surface) != SDL_TRUE)
			throw std::runtime_error(SDL_GetError());

		_eventHandlingID = _eventHandler.RegisterWindowEventCallback(WindowInternal::HandleWindowEventStatic, this, 0);
	}

	WindowInternal::~WindowInternal()
	{
		DestroyWindow();
	}

	void WindowInternal::CreateSwapchain(const VulkanSimplified::SwapchainCreationData& creationData, bool throwOnSwapchainExist)
	{
		if (_swapchain != VK_NULL_HANDLE)
		{
			if (throwOnSwapchainExist)
				throw std::runtime_error("WindowInternal::CreateSwapchain Error: Program tried to recreate a swapchain!");
			else
				DestroySwapchain();
		}

		_presentMode = TranslateToPresentMode(creationData.surfacePresentMode);
		_format = TranslateDataFormatToVkFormat(creationData.format);
		_swapchainFlags = 0;
		_imageAmount = creationData.imageAmount;

		_queueFamilies = _core.GetQueuesFamilies(creationData.queuesUsingSwapchain);

		std::stable_sort(_queueFamilies.begin(), _queueFamilies.end());
		_queueFamilies.erase(std::unique(_queueFamilies.begin(), _queueFamilies.end()), _queueFamilies.end());

		ReCreateSwapchain();
	}

	bool WindowInternal::AcquireNextImage(VkDevice device, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t& returnIndex)
	{
		if (device != _device)
			throw std::runtime_error("WindowInternal::AcquireNextImage Error: Program tried to used different device than swapchain was created with!");

		VkResult result = vkAcquireNextImageKHR(_device, _swapchain, timeout, semaphore, fence, &returnIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("WindowInternal::AcquireNextImage Error: Program failed to acquire next image!");

		return result == VK_SUCCESS;
	}

	VkSwapchainKHR WindowInternal::GetSwapchain() const
	{
		return _swapchain;
	}

	size_t WindowInternal::GetSwapchainImageAmount() const
	{
		return _swapchainImages.size();
	}

	VkImage WindowInternal::GetSwapchainImage(size_t imageIndex) const
	{
		if (_swapchain == VK_NULL_HANDLE)
			throw std::runtime_error("WindowInternal::GetSwapchainImage Error: Program tried to get an image from a non-existent swapchain!");

		if (_swapchainImages.size() <= imageIndex)
			throw std::runtime_error("WindowInternal::GetSwapchainImage Error: Program tried to get read beyond swapchain images list!");

		return _swapchainImages[imageIndex];
	}

	bool WindowInternal::IsHidden() const
	{
		return _hidden;
	}

	bool WindowInternal::IsMinimized() const
	{
		return _minimized;
	}

	bool WindowInternal::IsQuitingRequested() const
	{
		return _quit;
	}

	uint32_t WindowInternal::GetWidth() const
	{
		return _surfaceCapabilities.currentExtent.width;
	}

	uint32_t WindowInternal::GetHeight() const
	{
		return _surfaceCapabilities.currentExtent.height;
	}

	bool WindowInternal::HandleWindowEventStatic(const VulkanSimplified::SdlWindowEventData& event, void* windowptr)
	{
		return static_cast<WindowInternal*>(windowptr)->HandleWindowEvent(event);
	}

	void WindowInternal::DestroyWindow()
	{
		if (_eventHandlingID.has_value())
		{
			_eventHandler.UnRegisterWindowEventCallback(_eventHandlingID.value(), true);
			_eventHandlingID.reset();
		}

		if (_window != nullptr)
		{
			DestroySwapchain();

			vkDestroySurfaceKHR(_instance, _surface, nullptr);
			_surface = VK_NULL_HANDLE;

			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
	}

	void WindowInternal::ReCreateSwapchain()
	{
		DestroySwapchain();

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, _surface, &_surfaceCapabilities);
		ratio = static_cast<double>(std::min(_surfaceCapabilities.currentExtent.width, _surfaceCapabilities.currentExtent.height)) /
			static_cast<double>(std::max(_surfaceCapabilities.currentExtent.width, _surfaceCapabilities.currentExtent.height));

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.flags = _swapchainFlags;
		createInfo.surface = _surface;
		createInfo.minImageCount = _imageAmount;
		createInfo.imageFormat = _format;
		createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		createInfo.imageExtent.width = _surfaceCapabilities.currentExtent.width;
		createInfo.imageExtent.height = _surfaceCapabilities.currentExtent.height;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

		if (_queueFamilies.size() > 1)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(_queueFamilies.size());
			createInfo.pQueueFamilyIndices = _queueFamilies.data();
		}

		createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = _presentMode;
		createInfo.clipped = VK_TRUE;

		if (vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapchain) != VK_SUCCESS)
			throw std::runtime_error("Program failed to create the swapchain!");

		std::uint32_t imageCreated = 0;
		vkGetSwapchainImagesKHR(_device, _swapchain, &imageCreated, nullptr);
		_swapchainImages.resize(imageCreated);
		vkGetSwapchainImagesKHR(_device, _swapchain, &imageCreated, _swapchainImages.data());
	}

	void WindowInternal::DestroySwapchain()
	{
		if (_swapchain != VK_NULL_HANDLE)
		{
			vkDestroySwapchainKHR(_device, _swapchain, nullptr);
			_swapchain = VK_NULL_HANDLE;
			_swapchainImages.clear();
		}
	}

	VkPresentModeKHR WindowInternal::TranslateToPresentMode(VulkanSimplified::SurfacePresentModeBits presentMode)
	{
		VkPresentModeKHR ret = VK_PRESENT_MODE_MAX_ENUM_KHR;

		switch (presentMode)
		{
		case VulkanSimplified::PRESENT_MODE_IMMEDIATE:
			ret = VK_PRESENT_MODE_IMMEDIATE_KHR;
			break;
		case VulkanSimplified::PRESENT_MODE_MAILBOX:
			ret = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		case VulkanSimplified::PRESENT_MODE_FIFO_STRICT:
			ret = VK_PRESENT_MODE_FIFO_KHR;
			break;
		case VulkanSimplified::PRESENT_MODE_FIFO_RELAXED:
			ret = VK_PRESENT_MODE_FIFO_RELAXED_KHR;
			break;
		default:
			throw std::runtime_error("WindowInternal::TranslateToPresentMode Error: Program was given an erroneous present mode!");
		}

		return ret;
	}

	bool WindowInternal::HandleWindowEvent(const VulkanSimplified::SdlWindowEventData& event)
	{
		if (event.windowID != _windowID)
			return true;

		switch (event.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			_hidden = false;
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			_hidden = true;
			break;
		case SDL_WINDOWEVENT_RESIZED:
			if (_swapchain != VK_NULL_HANDLE)
				ReCreateSwapchain();
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			if (_swapchain != VK_NULL_HANDLE)
				ReCreateSwapchain();
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			_minimized = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			_quit = true;
			break;
		default:
			break;
		}

		return false;
	}

}