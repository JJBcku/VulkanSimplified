#pragma once

#include "../../../Include/VSCommon/VSCompositeAlphaFlags.h"

namespace VulkanSimplified
{
	VkCompositeAlphaFlagBitsKHR TranslateCompositeAlpha(CompositeAlphaFlagBits compositeAlpha);
}