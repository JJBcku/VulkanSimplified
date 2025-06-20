#pragma once

#include <vulkan/vulkan_core.h>
#include <stdint.h>
#include <compare>

namespace VulkanSimplified
{
	struct VertexAttributeDescriptionData
	{
		VkFormat format;
		uint32_t offset;

		VertexAttributeDescriptionData();

		bool operator==(const VertexAttributeDescriptionData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const VertexAttributeDescriptionData& rhs) const noexcept = default;
	};
}