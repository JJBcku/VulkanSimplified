#pragma once

#include "../../Include/VSCommon/VSImageSampleFlags.h"

namespace VulkanSimplifiedInternal
{
	VkSampleCountFlagBits TranslateImageSampleFlagBits(VulkanSimplified::ImageSampleFlagBits sampleCount);
}