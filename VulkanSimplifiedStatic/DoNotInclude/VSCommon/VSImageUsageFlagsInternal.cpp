#include "VSCommonNIpch.h"
#include "VSImageUsageFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	VkImageUsageFlags TranslateImageUsage(VulkanSimplified::ImageUsageFlags usageFlags)
	{
		VkImageUsageFlags ret = 0;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_TRANSFER_SRC) == VulkanSimplified::IMAGE_USAGE_TRANSFER_SRC)
			ret |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_TRANSFER_DST) == VulkanSimplified::IMAGE_USAGE_TRANSFER_DST)
			ret |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_SAMPLED) == VulkanSimplified::IMAGE_USAGE_SAMPLED)
			ret |= VK_IMAGE_USAGE_SAMPLED_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_STORAGE) == VulkanSimplified::IMAGE_USAGE_STORAGE)
			ret |= VK_IMAGE_USAGE_STORAGE_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_COLOR_ATTACHMENT) == VulkanSimplified::IMAGE_USAGE_COLOR_ATTACHMENT)
			ret |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT) == VulkanSimplified::IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT)
			ret |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_TRANSIENT_ATTACHMENT) == VulkanSimplified::IMAGE_USAGE_TRANSIENT_ATTACHMENT)
			ret |= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;

		if ((usageFlags & VulkanSimplified::IMAGE_USAGE_INPUT_ATTACHMENT) == VulkanSimplified::IMAGE_USAGE_INPUT_ATTACHMENT)
			ret |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		return ret;
	}
}