#include "VSDeviceNIpch.h"
#include "VSAutoCleanupNIFDescriptorPool.h"

#include "VSDescriptorPoolTypeCapacities.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupNIFDescriptorPool::AutoCleanupNIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount, const DescriptorPoolTypeCapacities& capacities) :
		_device(device), _pool(pool), _maxTotalSetCount(maxTotalSetCount), _currentSetCount(0)
	{
	}

	AutoCleanupNIFDescriptorPool::~AutoCleanupNIFDescriptorPool()
	{
		DestroyDescriptorPool();
	}

	AutoCleanupNIFDescriptorPool::AutoCleanupNIFDescriptorPool(AutoCleanupNIFDescriptorPool&& rhs) noexcept : _device(rhs._device), _pool(rhs._pool),
		_maxTotalSetCount(rhs._maxTotalSetCount), _currentSetCount(rhs._currentSetCount)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._pool = VK_NULL_HANDLE;

		rhs._maxTotalSetCount = 0;
		rhs._currentSetCount = 0;
	}

	AutoCleanupNIFDescriptorPool& AutoCleanupNIFDescriptorPool::operator=(AutoCleanupNIFDescriptorPool&& rhs) noexcept
	{
		_device = rhs._device;
		_pool = rhs._pool;

		_maxTotalSetCount = rhs._maxTotalSetCount;
		_currentSetCount = rhs._currentSetCount;

		rhs._device = VK_NULL_HANDLE;
		rhs._pool = VK_NULL_HANDLE;

		rhs._maxTotalSetCount = 0;
		rhs._currentSetCount = 0;

		return *this;
	}

	VkDevice AutoCleanupNIFDescriptorPool::GetDevice() const
	{
		return _device;
	}

	void AutoCleanupNIFDescriptorPool::DestroyDescriptorPool() noexcept
	{
		if (_pool != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorPool(_device, _pool, nullptr);
			_pool = VK_NULL_HANDLE;
		}
	}

}