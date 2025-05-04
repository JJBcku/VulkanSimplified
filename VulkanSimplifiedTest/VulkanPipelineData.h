#pragma once

#include <CustomLists/IDObject.h>

#include <VSPipelineDataListsDef.h>

struct VulkanPipelineData
{
	IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData();
};