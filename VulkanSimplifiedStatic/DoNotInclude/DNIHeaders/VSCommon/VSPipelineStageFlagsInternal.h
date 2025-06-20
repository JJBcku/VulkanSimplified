#pragma once

#include "../../../Include/VSCommon/VSPipelineStageFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	VkPipelineStageFlags TranslateStageFlags(PipelineStageFlags stageFlags);
}