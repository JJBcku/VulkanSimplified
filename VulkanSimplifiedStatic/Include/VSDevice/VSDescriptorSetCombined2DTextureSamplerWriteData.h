#pragma once

#include <CustomLists/IDObject.h>

#include "VSDescriptorDataListDef.h"
#include "VSImageDataListsDef.h"

#include "../VSCommon/VSImageLayoutFlags.h"

namespace VulkanSimplified
{
	typedef std::optional<std::pair<IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture>, IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>>> Optional2DTextureView;
	typedef std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupSampler>> OptionalSampler;
	typedef std::pair<Optional2DTextureView, OptionalSampler> Combined2DTextureSamplerIDs;

	struct DescriptorSetCombined2DTextureSamplerWriteData
	{
		IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet> descriptorSetID;
		uint32_t binding;
		uint32_t startArrayIndex;
		std::vector<std::pair<Combined2DTextureSamplerIDs, ImageLayoutFlags>> imageDataList;

		DescriptorSetCombined2DTextureSamplerWriteData();
	};
}
