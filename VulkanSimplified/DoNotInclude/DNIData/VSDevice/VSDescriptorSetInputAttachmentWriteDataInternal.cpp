#include "VSDeviceDNIpch.h"
#include "VSDescriptorSetInputAttachmentWriteDataInternal.h"

namespace VulkanSimplified
{
	DescriptorSetInputAttachmentWriteDataInternal::DescriptorSetInputAttachmentWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}

	DescriptorSetInputAttachmentWriteDataInternal::~DescriptorSetInputAttachmentWriteDataInternal()
	{
	}

}