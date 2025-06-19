#include "VSCommonNIpch.h"
#include "../../DNIHeaders/VSCommon/VSImageSampleFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	VkSampleCountFlagBits TranslateImageSampleFlagBits(VulkanSimplified::ImageSampleFlagBits sampleCount)
	{
		VkSampleCountFlagBits ret = VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM;

		switch (sampleCount)
		{
		case VulkanSimplified::SAMPLE_1:
			ret = VK_SAMPLE_COUNT_1_BIT;
			break;
		case VulkanSimplified::SAMPLE_2:
			ret = VK_SAMPLE_COUNT_2_BIT;
			break;
		case VulkanSimplified::SAMPLE_4:
			ret = VK_SAMPLE_COUNT_4_BIT;
			break;
		case VulkanSimplified::SAMPLE_8:
			ret = VK_SAMPLE_COUNT_8_BIT;
			break;
		case VulkanSimplified::SAMPLE_16:
			ret = VK_SAMPLE_COUNT_16_BIT;
			break;
		case VulkanSimplified::SAMPLE_32:
			ret = VK_SAMPLE_COUNT_32_BIT;
			break;
		case VulkanSimplified::SAMPLE_64:
			ret = VK_SAMPLE_COUNT_64_BIT;
			break;
		default:
			break;
		}

		return ret;
	}
}