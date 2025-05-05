#pragma once

#include <CustomLists/IDObjectDef.h>

#include "../VSCommon/VSPipelineStageFlagsDef.h"

#include "VSCommandBufferGenericIDDef.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupSemaphore;
}

namespace VulkanSimplified
{
	struct CommandBufferSubmissionData
	{
		std::vector<std::pair<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>, PipelineStageFlags>> waitSemaphores;
		std::vector<CommandBufferGenericID> commandBufferIDs;
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> signalSemaphores;

		CommandBufferSubmissionData() = default;
	};
}