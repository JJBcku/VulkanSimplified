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

	private:
		VulkanSimplifiedInternal::WindowInternal& _internal;
	};
}