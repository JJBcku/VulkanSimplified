#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupDescriptorSet.h"

namespace VulkanSimplified
{

	AutoCleanupDescriptorSet::AutoCleanupDescriptorSet(VkDescriptorSet set) : _set(set)
	{
	}

	AutoCleanupDescriptorSet::~AutoCleanupDescriptorSet()
	{
	}

	AutoCleanupDescriptorSet::AutoCleanupDescriptorSet(AutoCleanupDescriptorSet&& rhs) noexcept : _set(rhs._set)
	{
		rhs._set = VK_NULL_HANDLE;
	}

	AutoCleanupDescriptorSet& AutoCleanupDescriptorSet::operator=(AutoCleanupDescriptorSet&& rhs) noexcept
	{
		_set = rhs._set;
		rhs._set = VK_NULL_HANDLE;

		return *this;
	}

	VkDescriptorSet AutoCleanupDescriptorSet::GetDescriptorSet() const
	{
		return _set;
	}
}