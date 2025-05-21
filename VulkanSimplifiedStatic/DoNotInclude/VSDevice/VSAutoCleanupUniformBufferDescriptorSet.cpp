#include "VSDeviceNIpch.h"
#include "VSAutoCleanupUniformBufferDescriptorSet.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupUniformBufferDescriptorSet::AutoCleanupUniformBufferDescriptorSet(VkDescriptorSet set) : AutoCleanupDescriptorSet(set)
	{
	}

	AutoCleanupUniformBufferDescriptorSet::~AutoCleanupUniformBufferDescriptorSet()
	{
	}

}