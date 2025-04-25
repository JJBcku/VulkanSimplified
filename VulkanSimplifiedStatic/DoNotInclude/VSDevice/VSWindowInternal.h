#pragma once

#include "../../Include/VSCommon/VSSurfacePresentModesDef.h"

namespace VulkanSimplified
{
	struct WindowCreationData;
	struct SwapchainCreationData;

	enum SurfacePresentModeBits : SurfacePresentModes;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;

	class WindowInternal
	{
	public:
		WindowInternal(DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device, const VulkanSimplified::WindowCreationData& creationData);
		~WindowInternal();

		WindowInternal(const WindowInternal& rhs) noexcept = delete;
		WindowInternal(WindowInternal&& rhs) noexcept = delete;

		WindowInternal& operator=(const WindowInternal& rhs) noexcept = delete;
		WindowInternal& operator=(WindowInternal&& rhs) noexcept = delete;

		void CreateSwapchain(const VulkanSimplified::SwapchainCreationData& creationData, bool throwOnSwapchainExist);

	private:
		DeviceCoreInternal& _core;

		VkInstance _instance;
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		SDL_Window* _window;
		uint64_t _windowID;
		std::string _windowTitle;
		double ratio;

		VkSurfaceKHR _surface;
		VkSurfaceCapabilitiesKHR _surfaceCapabilities;

		VkPresentModeKHR _presentMode;
		VkFormat _format;
		VkSwapchainCreateFlagsKHR _swapchainFlags;
		uint32_t _imageAmount;

		std::vector<uint32_t> _queueFamilies;

		VkSwapchainKHR _swapchain;
		std::vector<VkImage> _swapchainImages;

		void DestroyWindow();

		void ReCreateSwapchain();
		void DestroySwapchain();

		VkPresentModeKHR TranslateToPresentMode(VulkanSimplified::SurfacePresentModeBits presentMode);
	};
}
