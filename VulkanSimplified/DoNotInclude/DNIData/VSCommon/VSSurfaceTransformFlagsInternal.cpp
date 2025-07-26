#include "VSCommonDNIpch.h"
#include "VSSurfaceTransformFlagsInternal.h"

namespace VulkanSimplified
{
	VkSurfaceTransformFlagBitsKHR TranslateSurfaceTransformFlag(SurfaceTransformFlagBits transformFlag)
	{
		VkSurfaceTransformFlagBitsKHR ret = VK_SURFACE_TRANSFORM_FLAG_BITS_MAX_ENUM_KHR;

		switch (transformFlag)
		{
		case VulkanSimplified::SURFACE_TRASFORM_IDENTITY:
			ret = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_ROTATE_90:
			ret = VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_ROTATE_180:
			ret = VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_ROTATE_270:
			ret = VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_HORIZONTAL_MIRROR:
			ret = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_HORIZONTAL_MIRROR_ROTATE_90:
			ret = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_HORIZONTAL_MIRROR_ROTATE_180:
			ret = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_HORIZONTAL_MIRROR_ROTATE_270:
			ret = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR;
			break;
		case VulkanSimplified::SURFACE_TRASFORM_INHERIT:
			ret = VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR;
			break;
		default:
			break;
		}

		return ret;
	}

	SurfaceTransformFlagBits TranslateSurfaceTransformFlag(VkSurfaceTransformFlagBitsKHR transformFlag)
	{
		SurfaceTransformFlagBits ret = static_cast<SurfaceTransformFlagBits>(0);

		switch (transformFlag)
		{
		case VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR:
			ret = SURFACE_TRASFORM_IDENTITY;
			break;
		case VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR:
			ret = SURFACE_TRASFORM_ROTATE_90;
			break;
		case VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR:
			ret = SURFACE_TRASFORM_ROTATE_180;
			break;
		case VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR:
			ret = SURFACE_TRASFORM_ROTATE_270;
			break;
		case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR:
			ret = SURFACE_TRASFORM_HORIZONTAL_MIRROR;
			break;
		case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR:
			ret = SURFACE_TRASFORM_HORIZONTAL_MIRROR_ROTATE_90;
			break;
		case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR:
			ret = SURFACE_TRASFORM_HORIZONTAL_MIRROR_ROTATE_180;
			break;
		case VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR:
			ret = SURFACE_TRASFORM_HORIZONTAL_MIRROR_ROTATE_270;
			break;
		case VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR:
			ret = SURFACE_TRASFORM_INHERIT;
			break;
		case VK_SURFACE_TRANSFORM_FLAG_BITS_MAX_ENUM_KHR:
			break;
		default:
			break;
		}

		return ret;
	}
}