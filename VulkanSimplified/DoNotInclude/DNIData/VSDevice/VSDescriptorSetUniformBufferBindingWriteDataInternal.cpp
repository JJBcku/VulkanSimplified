#include "VSDeviceDNIpch.h"
#include "VSDescriptorSetUniformBufferBindingWriteDataInternal.h"

namespace VulkanSimplified
{
	DescriptorSetUniformBufferBindingWriteDataInternal::DescriptorSetUniformBufferBindingWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}