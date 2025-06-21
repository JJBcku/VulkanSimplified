#pragma once

#include "../../../Include/VSCommon/VSImageLayoutFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	VkImageLayout TranslateImageLayout(ImageLayoutFlags imageLayout);
}