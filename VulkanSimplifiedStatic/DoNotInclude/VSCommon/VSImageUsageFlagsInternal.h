#pragma once

#include "../../Include/VSCommon/VSImageUsageFlagsDef.h"

namespace VulkanSimplifiedInternal
{
	VkImageUsageFlags TranslateImageUsage(VulkanSimplified::ImageUsageFlags usageFlags);
}