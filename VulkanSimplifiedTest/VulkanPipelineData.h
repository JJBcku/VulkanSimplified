#pragma once

#include <CustomLists/IDObject.h>

#include <VSPipelineDataListsDef.h>
#include <VSDescriptorDataListDef.h>

struct VulkanPipelineData
{
	IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> descriptorLayout;
	IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData();
};