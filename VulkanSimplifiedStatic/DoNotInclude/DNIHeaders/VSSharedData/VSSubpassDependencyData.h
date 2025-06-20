#pragma once

#include <vulkan/vulkan_core.h>
#include <stdint.h>
#include <compare>

namespace VulkanSimplified
{
	struct SubpassDependencyData
	{
		uint32_t srcSubpass;
		uint32_t dstSubpass;
		VkPipelineStageFlags srcStageFlags;
		VkPipelineStageFlags dstStageFlags;
		VkAccessFlags srcAccessFlags;
		VkAccessFlags dstAccessFlags;

		SubpassDependencyData();

		bool operator==(const SubpassDependencyData&) const noexcept = default;
		std::strong_ordering operator<=>(const SubpassDependencyData&) const noexcept = default;
	};
}