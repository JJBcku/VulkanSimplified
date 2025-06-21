#include "VSDeviceNIpch.h"
#include "VSAutoCleanupFramebuffer.h"

namespace VulkanSimplified
{
	AutoCleanupFramebuffer::AutoCleanupFramebuffer(VkDevice device, VkFramebuffer framebuffer) : _device(device), _framebuffer(framebuffer)
	{
	}

	AutoCleanupFramebuffer::~AutoCleanupFramebuffer()
	{
		DestroyFramebuffer();
	}

	AutoCleanupFramebuffer::AutoCleanupFramebuffer(AutoCleanupFramebuffer&& rhs) noexcept : _device(rhs._device), _framebuffer(rhs._framebuffer)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._framebuffer = VK_NULL_HANDLE;
	}

	AutoCleanupFramebuffer& AutoCleanupFramebuffer::operator=(AutoCleanupFramebuffer&& rhs) noexcept
	{
		DestroyFramebuffer();

		_device = rhs._device;
		_framebuffer = rhs._framebuffer;

		rhs._device = VK_NULL_HANDLE;
		rhs._framebuffer = VK_NULL_HANDLE;

		return *this;
	}

	VkFramebuffer AutoCleanupFramebuffer::GetFramebuffer() const
	{
		return _framebuffer;
	}

	void AutoCleanupFramebuffer::DestroyFramebuffer()
	{
		if (_framebuffer != VK_NULL_HANDLE)
		{
			vkDestroyFramebuffer(_device, _framebuffer, nullptr);
			_framebuffer = VK_NULL_HANDLE;
		}
	}
}