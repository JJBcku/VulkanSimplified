#include "VSDeviceNIpch.h"
#include "VSUniformBufferDescriptorSetWriteDataInternal.h"

namespace VulkanSimplifiedInternal
{
	UniformBufferDescriptorSetWriteDataInternal::UniformBufferDescriptorSetWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}