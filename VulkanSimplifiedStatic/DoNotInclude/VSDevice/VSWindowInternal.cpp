#include "VSDeviceNIpch.h"
#include "VSWindowInternal.h"

#include "../../Include/VSDevice/VSWindowCreationData.h"
#include "../../Include/VSDevice/VSSwapchainCreationData.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"

#include "VSDeviceCoreInternal.h"

namespace VulkanSimplifiedInternal
{
	WindowInternal::WindowInternal(DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
		const VulkanSimplified::WindowCreationData& creationData) : _core(core)
	{
		_instance = instance;
		_physicalDevice = physicalDevice;
		_device = device;

		_window = nullptr;
		_windowTitle = creationData.windowTitle;
		_width = creationData.width;
		_height = creationData.height;

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

		_window = SDL_CreateWindow(_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(_width), static_cast<int>(_height), flags);

		if (_window == nullptr)
			throw std::runtime_error(SDL_GetError());

		_windowID = SDL_GetWindowID(_window);

		if (_windowID == 0)
			throw std::runtime_error(SDL_GetError());

		if (SDL_Vulkan_CreateSurface(_window, _instance, &_surface) != SDL_TRUE)
			throw std::runtime_error(SDL_GetError());
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

	/*WindowInternal::WindowInternal(WindowInternal&& rhs) noexcept : _instance(rhs._instance), _device(rhs._device), _window(rhs._window), _windowID(rhs._windowID),
		_windowTitle(std::move(rhs._windowTitle)), _width(rhs._width), _height(rhs._height), _surface(rhs._surface), _surfaceCapabilities(rhs._surfaceCapabilities),
		_swapchain(rhs._swapchain)
	{
		rhs._instance = VK_NULL_HANDLE;
		rhs._device = VK_NULL_HANDLE;

		rhs._window = nullptr;
		rhs._windowID = 0;
		rhs._width = 0;
		rhs._height = 0;

		rhs._surface = VK_NULL_HANDLE;
		rhs._surfaceCapabilities = {};

		rhs._surfacePresentMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
		rhs._format = VK_FORMAT_MAX_ENUM;
		rhs._swapchainFlags = VK_SWAPCHAIN_CREATE_FLAG_BITS_MAX_ENUM_KHR;
		rhs._imageAmount = 0;

		rhs._swapchain = VK_NULL_HANDLE;
	}

	WindowInternal& WindowInternal::operator=(WindowInternal&& rhs) noexcept
	{
		DestroyWindow();

		_instance = rhs._instance;
		_device = rhs._device;

		_window = rhs._window;
		_windowID = rhs._windowID;
		_windowTitle = std::move(rhs._windowTitle);
		_width = rhs._width;
		_height = rhs._height;

		_surface = rhs._surface;
		_surfaceCapabilities = rhs._surfaceCapabilities;

		_surfacePresentMode = rhs._surfacePresentMode;
		_format = rhs._format;
		_swapchainFlags = rhs._swapchainFlags;
		_imageAmount = rhs._imageAmount;

		_queueFamilies = std::move(rhs._queueFamilies);

		_swapchain = rhs._swapchain;
		_swapchainImages = std::move(rhs._swapchainImages);

		rhs._instance = VK_NULL_HANDLE;
		rhs._device = VK_NULL_HANDLE;

		rhs._window = nullptr;
		rhs._windowID = 0;
		rhs._width = 0;
		rhs._height = 0;

		rhs._surface = VK_NULL_HANDLE;
		rhs._surfaceCapabilities = {};

		rhs._surfacePresentMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
		rhs._format = VK_FORMAT_MAX_ENUM;
		rhs._swapchainFlags = VK_SWAPCHAIN_CREATE_FLAG_BITS_MAX_ENUM_KHR;
		rhs._imageAmount = 0;

		rhs._swapchain = VK_NULL_HANDLE;

		return *this;
	}*/

	void WindowInternal::DestroyWindow()
	{
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

}