#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	class PipelineDataListsInternal;
	class AutoCleanupPipelineLayout;
	class AutoCleanupGraphicsPipeline;
}

struct VulkanPipelineData
{
	IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData();
};