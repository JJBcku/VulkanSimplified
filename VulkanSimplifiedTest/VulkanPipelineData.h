#pragma once

#include <CustomLists/IDObject.h>

#include <VSPipelineDataListsDef.h>
#include <VSDescriptorDataListDef.h>

struct VulkanPipelineData
{
	IDObject<VS::AutoCleanupDescriptorSetLayout> descriptorLayout;
	IDObject<VS::AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<VS::AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData();
};