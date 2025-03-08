#include "VSDeviceIpch.h"
#include "VSWindow.h"

#include "../../DoNotInclude/VSDevice/VSWindowInternal.h"

namespace VulkanSimplified
{
	Window::Window(VulkanSimplifiedInternal::WindowInternal& ref) : _internal(ref)
	{
	}

	Window::~Window()
	{
	}

	void Window::CreateSwapchain(const VulkanSimplified::SwapchainCreationData& creationData, bool throwOnSwapchainExist)
	{
		_internal.CreateSwapchain(creationData, throwOnSwapchainExist);
	}

}