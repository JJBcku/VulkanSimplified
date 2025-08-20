#pragma once

#include <CustomLists/IDObject.h>

#include "../../../Include/VSDevice/VSDescriptorDataListsDef.h"

namespace VulkanSimplified
{
	struct DescriptorSetInputAttachmentWriteDataInternal
	{
		IDObject<AutoCleanupDescriptorSet> descriptorSetID;
		uint32_t binding;
		uint32_t startArrayIndex;
		std::vector<VkDescriptorImageInfo> imageInfo;

		DescriptorSetInputAttachmentWriteDataInternal();
		~DescriptorSetInputAttachmentWriteDataInternal();
	};
}
