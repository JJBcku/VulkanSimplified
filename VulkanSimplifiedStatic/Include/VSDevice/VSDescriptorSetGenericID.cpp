#include "VSDeviceIpch.h"
#include "VSDescriptorSetGenericID.h"

namespace VulkanSimplified
{
	DescriptorSetGenericID::DescriptorSetGenericID()
	{
		type = DescriptorSetIDType::UNKNOWN;
	}

	DescriptorSetGenericID::DescriptorSetGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet> ID)
	{
		uniformBufferID.type = DescriptorSetIDType::UNIFORM_BUFFER;
		uniformBufferID.ID = ID;
	}

}