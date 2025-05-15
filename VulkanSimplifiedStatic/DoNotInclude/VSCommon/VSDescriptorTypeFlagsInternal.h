#pragma once

#include "../../Include/VSCommon/VSDescriptorTypeFlags.h"

namespace VulkanSimplifiedInternal
{
	VkDescriptorType TranslateDescriptorTypeFlags(VulkanSimplified::DescriptorTypeFlagBits descriptorType);
}