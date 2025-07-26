#include "VSCommonDNIpch.h"
#include "VSCompositeAlphaFlagsInternal.h"

VkCompositeAlphaFlagBitsKHR VulkanSimplified::TranslateCompositeAlpha(CompositeAlphaFlagBits compositeAlpha)
{
	VkCompositeAlphaFlagBitsKHR ret = VK_COMPOSITE_ALPHA_FLAG_BITS_MAX_ENUM_KHR;

	switch (compositeAlpha)
	{
	case VulkanSimplified::COMPOSITE_ALPHA_OPAQUE:
		ret = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		break;
	case VulkanSimplified::COMPOSITE_ALPHA_PRE_MULTIPLIED:
		ret = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
		break;
	case VulkanSimplified::COMPOSITE_ALPHA_POST_MULTIPLIED:
		ret = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
		break;
	default:
		break;
	}

	return ret;
}
