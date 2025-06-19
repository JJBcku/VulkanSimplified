#pragma once

#include <vulkan/vulkan_core.h>
#include <stdint.h>
#include <compare>

namespace VulkanSimplifiedInternal
{
	struct PushConstantData
	{
		VkShaderStageFlags shaderStages;
		uint32_t offset;
		uint32_t size;
		uint32_t padding;

		PushConstantData();

		bool operator==(const PushConstantData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const PushConstantData& rhs) const noexcept = default;
	};
}