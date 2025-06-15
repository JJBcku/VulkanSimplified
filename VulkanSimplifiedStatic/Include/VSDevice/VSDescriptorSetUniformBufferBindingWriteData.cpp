#include "VSDeviceIpch.h"
#include "VSDescriptorSetUniformBufferBindingWriteData.h"

namespace VulkanSimplified
{
	DescriptorSetUniformBufferBindingWriteData::DescriptorSetUniformBufferBindingWriteData()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}