#pragma once

#include <vulkan/vulkan_core.h>

#include <compare>
#include <stdint.h>

namespace VulkanSimplified
{
	struct DescriptorSetLayoutBindingData
	{
		VkDescriptorType descriptorType;
		uint32_t descriptorCount;
		VkShaderStageFlags shaderStages;
		uint32_t padding;

		DescriptorSetLayoutBindingData();

		bool operator==(const DescriptorSetLayoutBindingData&) const noexcept = default;
		std::strong_ordering operator<=>(const DescriptorSetLayoutBindingData&) const noexcept = default;
	};
}