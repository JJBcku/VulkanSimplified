#pragma once

#include "../../../Include/VSCommon/VSDataFormatFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	VkFormat TranslateDataFormatToVkFormat(DataFormatSetIndependentID formatID);
}