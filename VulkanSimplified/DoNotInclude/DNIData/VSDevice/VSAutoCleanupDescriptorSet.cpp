#include "VSDeviceNIpch.h"
#include "VSAutoCleanupDescriptorSet.h"

namespace VulkanSimplified
{

	AutoCleanupDescriptorSet::AutoCleanupDescriptorSet(VkDescriptorSet set) : _set(set)
	{
	}

	AutoCleanupDescriptorSet::~AutoCleanupDescriptorSet()
	{
	}

	VkDescriptorSet AutoCleanupDescriptorSet::GetDescriptorSet() const
	{
		return _set;
	}
}