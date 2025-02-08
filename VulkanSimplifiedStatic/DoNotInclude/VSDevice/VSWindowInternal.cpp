#include "VSDeviceNIpch.h"
#include "VSWindowInternal.h"

#include "../../Include/VSDevice/VSWindowCreationData.h"

namespace VulkanSimplifiedInternal
{
	WindowInternal::WindowInternal(VkInstance instance, VkDevice device, const VulkanSimplified::WindowCreationData& creationData)
	{
		_instance = instance;
		_device = device;

		_window = nullptr;
		_windowTitle = creationData.windowTitle;
		_width = creationData.width;
		_height = creationData.height;

		_surface = VK_NULL_HANDLE;

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

	WindowInternal::WindowInternal(WindowInternal&& rhs) noexcept : _instance(rhs._instance), _device(rhs._device), _window(rhs._window), _windowID(rhs._windowID),
		_windowTitle(std::move(rhs._windowTitle)), _width(rhs._width), _height(rhs._height), _surface(rhs._surface), _swapchain(rhs._swapchain)
	{
		rhs._instance = VK_NULL_HANDLE;
		rhs._device = VK_NULL_HANDLE;

		rhs._window = nullptr;
		rhs._windowID = 0;
		rhs._width = 0;
		rhs._height = 0;

		rhs._surface = VK_NULL_HANDLE;

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

		_swapchain = rhs._swapchain;

		rhs._instance = VK_NULL_HANDLE;
		rhs._device = VK_NULL_HANDLE;

		rhs._window = nullptr;
		rhs._windowID = 0;
		rhs._width = 0;
		rhs._height = 0;

		rhs._surface = VK_NULL_HANDLE;

		rhs._swapchain = VK_NULL_HANDLE;

		return *this;
	}

	void WindowInternal::DestroyWindow()
	{
		if (_window != nullptr)
		{
			vkDestroySurfaceKHR(_instance, _surface, nullptr);
			_surface = VK_NULL_HANDLE;

			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
	}

}