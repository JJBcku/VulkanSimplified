#pragma once

#include "../../../Include/VSDevice/VSDescriptorDataListsDef.h"

#include <CustomLists/IDObject.h>

#include <cstdint>
#include <vector>

struct VkDescriptorImageInfo;

namespace VulkanSimplified
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