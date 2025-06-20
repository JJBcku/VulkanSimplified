#pragma once

#include "../../../Include/VSCommon/VSImageSampleFlags.h"

#include <stdint.h>
#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	VkSampleCountFlagBits TranslateImageSampleFlagBits(ImageSampleFlagBits sampleCount);
}