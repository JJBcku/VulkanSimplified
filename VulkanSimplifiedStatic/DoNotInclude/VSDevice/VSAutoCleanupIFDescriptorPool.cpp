#include "VSDeviceNIpch.h"
#include "VSAutoCleanupIFDescriptorPool.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupIFDescriptorPool::AutoCleanupIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxSetCount, const DescriptorPoolTypeCapacities& capacities) :
		AutoCleanupNIFDescriptorPool(device, pool, maxSetCount, capacities)
	{
	}

	AutoCleanupIFDescriptorPool::~AutoCleanupIFDescriptorPool()
	{
	}

}