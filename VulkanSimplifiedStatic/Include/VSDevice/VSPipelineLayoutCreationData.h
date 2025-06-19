#pragma once

#include <CustomLists/IDObject.h>

#include <vector>

namespace VulkanSimplifiedInternal
{
	class AutoCleanupDescriptorSetLayout;
	struct PushConstantData;
}

namespace VulkanSimplified
{
	struct PipelineLayoutCreationData
	{
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> _descriptorSets;
		std::vector<IDObject<VulkanSimplifiedInternal::PushConstantData>> _pushConstants;

		PipelineLayoutCreationData() = default;
	};
}