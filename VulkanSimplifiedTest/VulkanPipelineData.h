#pragma once

#include <CustomLists/IDObject.h>

#include <VSPipelineDataListsDef.h>
#include <VSDescriptorDataListDef.h>

struct VulkanPipelineData
{
	IDObject<VulkanSimplified::AutoCleanupDescriptorSetLayout> descriptorLayout;
	IDObject<VulkanSimplified::AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<VulkanSimplified::AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData();
};