#pragma once

#include "../../../Include/VSCommon/VSSurfacePresentModesDef.h"

#include "../../../Include/VSMain/EventHandler/SdlEventHandlerTypedefs.h"

#include <Miscellaneous/Bool64Def.h>
#include <CustomLists/IDObject.h>

struct SDL_Window;

#include <vulkan/vulkan.hpp>
#include <stdint.h>
#include <vector>
#include <string>
#include <optional>

namespace VulkanSimplified
{
	struct WindowCreationData;
	struct SwapchainCreationData;

	enum SurfacePresentModeBits : SurfacePresentModes;

	struct SdlWindowEventData;
}

namespace VulkanSimplified
{
	class DeviceCoreInternal;
	class SdlEventHandlerInternal;

	class WindowInternal
	{
	public:
		WindowInternal(SdlEventHandlerInternal& eventHandler, DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
			const WindowCreationData& creationData);
		~WindowInternal();

		WindowInternal(const WindowInternal& rhs) noexcept = delete;
		WindowInternal(WindowInternal&& rhs) noexcept = delete;

		WindowInternal& operator=(const WindowInternal& rhs) noexcept = delete;
		WindowInternal& operator=(WindowInternal&& rhs) noexcept = delete;

		void CreateSwapchain(const SwapchainCreationData& creationData, bool throwOnSwapchainExist);

		bool AcquireNextImage(VkDevice device, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t& returnIndex);

		VkSwapchainKHR GetSwapchain() const;

		size_t GetSwapchainImageAmount() const;
		VkImage GetSwapchainImage(size_t imageIndex) const;

		bool IsHidden() const;
		bool IsMinimized() const;
		bool IsQuitingRequested() const;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		void SetFullscreen(Misc::Bool64Values newFullscreenValue);

	private:
		SdlEventHandlerInternal& _eventHandler;
		DeviceCoreInternal& _core;

		VkInstance _instance;
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		bool _hidden;
		bool _minimized;
		bool _quit;
		bool _bpadding;
		uint32_t _windowID;

		Misc::Bool64Values _isBorderlessNoFullscreen;
		Misc::Bool64Values _isFullscreen;

		std::optional<IDObject<std::pair<WindowEventFunction, void*>>> _eventHandlingID;

		SDL_Window* _window;
		std::string _windowTitle;
		double _aspectRatio;

		VkSurfaceKHR _surface;
		VkSurfaceCapabilitiesKHR _surfaceCapabilities;

		VkCompositeAlphaFlagBitsKHR _compositeAlphaMode;
		VkSurfaceTransformFlagBitsKHR _transformMode;
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

		VkPresentModeKHR TranslateToPresentMode(SurfacePresentModeBits presentMode);

		bool HandleWindowEvent(const SdlWindowEventData& event);
		static bool HandleWindowEventStatic(const SdlWindowEventData& event, void* windowptr);
	};
}
