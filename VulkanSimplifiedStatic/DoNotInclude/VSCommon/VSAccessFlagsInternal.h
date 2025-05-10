#pragma once

#include "../../Include/VSCommon/VSAccessFlags.h"

namespace VulkanSimplifiedInternal
{
	VkAccessFlags TranslataAccessFlags(VulkanSimplified::AccessFlags accessFlags);
}