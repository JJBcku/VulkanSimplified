#pragma once

#include "../../Include/VSCommon/VSImageSampleFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplifiedInternal
{
	VkSampleCountFlagBits TranslateImageSampleFlagBits(VulkanSimplified::ImageSampleFlagBits sampleCount);
}