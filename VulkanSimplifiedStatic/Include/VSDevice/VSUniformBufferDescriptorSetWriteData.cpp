#include "VSDeviceIpch.h"
#include "VSUniformBufferDescriptorSetWriteData.h"

namespace VulkanSimplified
{
	UniformBufferDescriptorSetWriteData::UniformBufferDescriptorSetWriteData()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}