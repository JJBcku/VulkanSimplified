#pragma once

#include "../../../Include/VSCommon/VSAccessFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplifiedInternal
{
	VkAccessFlags TranslataAccessFlags(VulkanSimplified::AccessFlags accessFlags);
}