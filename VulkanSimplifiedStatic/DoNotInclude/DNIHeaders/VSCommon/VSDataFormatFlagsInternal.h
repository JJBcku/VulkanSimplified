#pragma once

#include "../../../Include/VSCommon/VSDataFormatFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplifiedInternal
{
	VkFormat TranslateDataFormatToVkFormat(VulkanSimplified::DataFormatSetIndependentID formatID);
}