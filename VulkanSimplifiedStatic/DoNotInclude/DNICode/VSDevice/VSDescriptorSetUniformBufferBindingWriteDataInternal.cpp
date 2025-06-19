#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSDescriptorSetUniformBufferBindingWriteDataInternal.h"

namespace VulkanSimplifiedInternal
{
	DescriptorSetUniformBufferBindingWriteDataInternal::DescriptorSetUniformBufferBindingWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}