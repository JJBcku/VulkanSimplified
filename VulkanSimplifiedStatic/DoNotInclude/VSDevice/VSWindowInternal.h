#pragma once

namespace VulkanSimplified
{
	struct WindowCreationData;
}

namespace VulkanSimplifiedInternal
{
	class WindowInternal
	{
	public:
		WindowInternal(VkInstance instance, VkDevice device, const VulkanSimplified::WindowCreationData& creationData);
		~WindowInternal();

		WindowInternal(const WindowInternal& rhs) noexcept = delete;
		WindowInternal(WindowInternal&& rhs) noexcept;

		WindowInternal& operator=(const WindowInternal& rhs) noexcept = delete;
		WindowInternal& operator=(WindowInternal&& rhs) noexcept;

	private:
		VkInstance _instance;
		VkDevice _device;

		SDL_Window* _window;
		uint64_t _windowID;
		std::string _windowTitle;
		uint32_t _width;
		uint32_t _height;

		VkSurfaceKHR _surface;

		VkSwapchainKHR _swapchain;

		void DestroyWindow();
	};
}
