#pragma once

#include "../../../Include/VSCommon/VSSurfaceTransformFlags.h"

namespace VulkanSimplified
{
	VkSurfaceTransformFlagBitsKHR TranslateSurfaceTransformFlag(SurfaceTransformFlagBits transformFlag);
	SurfaceTransformFlagBits TranslateSurfaceTransformFlag(VkSurfaceTransformFlagBitsKHR transformFlag);
}