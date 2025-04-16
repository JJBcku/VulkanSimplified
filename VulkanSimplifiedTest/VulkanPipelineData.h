#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	class PipelineDataListsInternal;
	class AutoCleanupPipelineLayout;
}

struct VulkanPipelineData
{
	IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> pipelineLayout;

	VulkanPipelineData();
};