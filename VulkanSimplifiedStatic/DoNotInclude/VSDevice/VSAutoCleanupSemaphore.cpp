#include "VSDeviceNIpch.h"
#include"VSAutoCleanupSemaphore.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupSemaphore::AutoCleanupSemaphore(VkDevice device, VkSemaphore semaphore) : _device(device), _semaphore(semaphore)
	{
	}

	AutoCleanupSemaphore::~AutoCleanupSemaphore()
	{
		DestroySemaphore();
	}

	AutoCleanupSemaphore::AutoCleanupSemaphore(AutoCleanupSemaphore&& rhs) noexcept : _device(rhs._device), _semaphore(rhs._semaphore)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._semaphore = VK_NULL_HANDLE;
	}

	AutoCleanupSemaphore& AutoCleanupSemaphore::operator=(AutoCleanupSemaphore&& rhs) noexcept
	{
		DestroySemaphore();

		_device = rhs._device;
		_semaphore = rhs._semaphore;

		rhs._device = VK_NULL_HANDLE;
		rhs._semaphore = VK_NULL_HANDLE;
		return *this;
	}

	VkSemaphore AutoCleanupSemaphore::GetSemaphore() const
	{
		return _semaphore;
	}

	void AutoCleanupSemaphore::DestroySemaphore()
	{
		if (_semaphore != VK_NULL_HANDLE)
		{
			vkDestroySemaphore(_device, _semaphore, nullptr);
			_semaphore = VK_NULL_HANDLE;
		}
	}
}