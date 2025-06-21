#include "VSSharedDNIpch.h"
#include "VSDescriptorSetLayoutBindingData.h"

namespace VulkanSimplified
{
	DescriptorSetLayoutBindingData::DescriptorSetLayoutBindingData()
	{
		descriptorType = VK_DESCRIPTOR_TYPE_MAX_ENUM;
		descriptorCount = std::numeric_limits<uint32_t>::max();
		shaderStages = 0;
		padding = 0;
	}
}