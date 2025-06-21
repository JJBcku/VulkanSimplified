#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSWindow.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSWindowInternal.h"

namespace VulkanSimplified
{
	Window::Window(WindowInternal& ref) : _internal(ref)
	{
	}

	Window::~Window()
	{
	}

	void Window::CreateSwapchain(const SwapchainCreationData& creationData, bool throwOnSwapchainExist)
	{
		_internal.CreateSwapchain(creationData, throwOnSwapchainExist);
	}

	size_t Window::GetSwapchainImageAmount() const
	{
		return _internal.GetSwapchainImageAmount();
	}

	bool Window::IsHidden() const
	{
		return _internal.IsHidden();
	}

	bool Window::IsMinimized() const
	{
		return _internal.IsMinimized();
	}

	bool Window::IsQuitingRequested() const
	{
		return _internal.IsQuitingRequested();
	}

	uint32_t Window::GetWidth() const
	{
		return _internal.GetWidth();
	}

	uint32_t Window::GetHeight() const
	{
		return _internal.GetHeight();
	}

}