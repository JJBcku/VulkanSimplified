#pragma once

#include "../../Include/VSCommon/VSImageLayoutFlags.h"

namespace VulkanSimplifiedInternal
{
	VkImageLayout TranslateImageLayout(VulkanSimplified::ImageLayoutFlags imageLayout);
}