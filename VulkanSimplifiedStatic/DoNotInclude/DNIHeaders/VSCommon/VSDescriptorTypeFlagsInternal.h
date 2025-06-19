#pragma once

#include "../../../Include/VSCommon/VSDescriptorTypeFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplifiedInternal
{
	VkDescriptorType TranslateDescriptorTypeFlags(VulkanSimplified::DescriptorTypeFlagBits descriptorType);
}