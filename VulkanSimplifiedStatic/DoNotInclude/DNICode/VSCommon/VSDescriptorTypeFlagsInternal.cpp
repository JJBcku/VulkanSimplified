#include "VSCommonNIpch.h"
#include "../../DNIHeaders/VSCommon/VSDescriptorTypeFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	VkDescriptorType TranslateDescriptorTypeFlags(VulkanSimplified::DescriptorTypeFlagBits descriptorType)
	{
		VkDescriptorType ret = VK_DESCRIPTOR_TYPE_MAX_ENUM;

		switch (descriptorType)
		{
		case VulkanSimplified::DescriptorTypeFlagBits::SAMPLER:
			ret = VK_DESCRIPTOR_TYPE_SAMPLER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER:
			ret = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::SAMPLED_IMAGE:
			ret = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_IMAGE:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_TEXEL_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_TEXEL_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER_DYNAMIC:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_BUFFER_DYNAMIC:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::INPUT_ATTACHMENT:
			ret = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			break;
		default:
			break;
		}

		return ret;
	}
}