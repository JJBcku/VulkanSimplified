#pragma once

#include <CustomLists/IDObject.h>

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

namespace VulkanSimplifiedInternal
{
	struct DescriptorSetCombined2DTextureSamplerWriteDataInternal
	{
		IDObject<AutoCleanupDescriptorSet> descriptorSetID;
		uint32_t binding;
		uint32_t startArrayIndex;
		std::vector<VkDescriptorImageInfo> imageInfo;

		DescriptorSetCombined2DTextureSamplerWriteDataInternal();
	};
}