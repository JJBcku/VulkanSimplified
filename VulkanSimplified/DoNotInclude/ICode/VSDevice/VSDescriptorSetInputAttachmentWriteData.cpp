#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDescriptorSetInputAttachmentWriteData.h"

namespace VulkanSimplified
{
	DescriptorSetInputAttachmentWriteData::DescriptorSetInputAttachmentWriteData()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}

	DescriptorSetInputAttachmentWriteData::~DescriptorSetInputAttachmentWriteData()
	{
	}
}