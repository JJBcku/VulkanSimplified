#pragma once

#include "../../Include/VSCommon/VSPipelineStageFlags.h"

namespace VulkanSimplifiedInternal
{
	VkPipelineStageFlags TranslateStageFlags(VulkanSimplified::PipelineStageFlags stageFlags);
}