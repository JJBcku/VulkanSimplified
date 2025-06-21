#include "VSCommonDNIpch.h"
#include "VSDescriptorTypeFlagsInternal.h"

namespace VulkanSimplified
{
	VkDescriptorType TranslateDescriptorTypeFlags(DescriptorTypeFlagBits descriptorType)
	{
		VkDescriptorType ret = VK_DESCRIPTOR_TYPE_MAX_ENUM;

		switch (descriptorType)
		{
		case DescriptorTypeFlagBits::SAMPLER:
			ret = VK_DESCRIPTOR_TYPE_SAMPLER;
			break;
		case DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER:
			ret = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			break;
		case DescriptorTypeFlagBits::SAMPLED_IMAGE:
			ret = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			break;
		case DescriptorTypeFlagBits::STORAGE_IMAGE:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			break;
		case DescriptorTypeFlagBits::UNIFORM_TEXEL_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			break;
		case DescriptorTypeFlagBits::STORAGE_TEXEL_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			break;
		case DescriptorTypeFlagBits::UNIFORM_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			break;
		case DescriptorTypeFlagBits::STORAGE_BUFFER:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			break;
		case DescriptorTypeFlagBits::UNIFORM_BUFFER_DYNAMIC:
			ret = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			break;
		case DescriptorTypeFlagBits::STORAGE_BUFFER_DYNAMIC:
			ret = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			break;
		case DescriptorTypeFlagBits::INPUT_ATTACHMENT:
			ret = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			break;
		default:
			break;
		}

		return ret;
	}
}