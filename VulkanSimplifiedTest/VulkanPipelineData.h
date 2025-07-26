#pragma once

#include <CustomLists/IDObject.h>

#include <VSPipelineDataListsDef.h>
#include <VSDescriptorDataListsDef.h>

struct VulkanPipelineData
{
	IDObject<VS::AutoCleanupDescriptorSetLayout> descriptorLayout;
	IDObject<VS::AutoCleanupPipelineLayout> pipelineLayout;
	IDObject<VS::AutoCleanupGraphicsPipeline> pipeline;

	VulkanPipelineData();
};