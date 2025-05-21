#include "VSDeviceNIpch.h"
#include "VSAutoCleanupDescriptorSet.h"

namespace VulkanSimplifiedInternal
{

	VkDescriptorSet AutoCleanupDescriptorSet::GetDescriptorSet() const
	{
		return _set;
	}

	AutoCleanupDescriptorSet::AutoCleanupDescriptorSet(VkDescriptorSet set) : _set(set)
	{
	}

	AutoCleanupDescriptorSet::~AutoCleanupDescriptorSet()
	{
	}
}