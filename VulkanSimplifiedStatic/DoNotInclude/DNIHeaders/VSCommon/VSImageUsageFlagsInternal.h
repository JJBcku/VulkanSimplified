#pragma once

#include "../../../Include/VSCommon/VSImageUsageFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	VkImageUsageFlags TranslateImageUsage(ImageUsageFlags usageFlags);
}