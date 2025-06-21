#pragma once

#include "../../../Include/VSCommon/VSDescriptorTypeFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	VkDescriptorType TranslateDescriptorTypeFlags(DescriptorTypeFlagBits descriptorType);
}