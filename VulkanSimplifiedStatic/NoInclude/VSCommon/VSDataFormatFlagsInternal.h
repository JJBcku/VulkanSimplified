#pragma once

#include "../../Include/VSCommon/VSDataFormatFlags.h"

namespace VulkanSimplifiedInternal
{
	VkFormat TranslateDataFormatToVkFormat(VulkanSimplified::DataFormatSetIndependentID formatID);
}