#pragma once

namespace VulkanSimplifiedInternal
{
	class WindowInternal;
}

namespace VulkanSimplified
{
	struct SwapchainCreationData;

	class Window
	{
	public:
		Window(VulkanSimplifiedInternal::WindowInternal& ref);
		~Window();

		void CreateSwapchain(const VulkanSimplified::SwapchainCreationData& creationData, bool throwOnSwapchainExist);

		size_t GetSwapchainImageAmount() const;

		bool IsHidden() const;
		bool IsMinimized() const;
		bool IsQuitingRequested() const;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

	private:
		VulkanSimplifiedInternal::WindowInternal& _internal;
	};
}