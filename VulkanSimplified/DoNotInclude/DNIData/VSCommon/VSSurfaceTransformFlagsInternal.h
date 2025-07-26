#pragma once

#include "../../../Include/VSCommon/VSSurfaceTransformFlagsDef.h"

namespace VulkanSimplified
{
	VkSurfaceTransformFlagBitsKHR TranslateSurfaceTransformFlag(SurfaceTransformFlagBits transformFlag);
	SurfaceTransformFlagBits TranslateSurfaceTransformFlag(VkSurfaceTransformFlagBitsKHR transformFlag);
}