#pragma once

#include <CustomLists/IDObject.h>

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdint.h>
#include <compare>

namespace VulkanSimplifiedInternal
{
	struct VertexAttributeDescriptionData;

	struct VertexBindingDescriptionData
	{
		uint32_t stride;
		VkVertexInputRate inputRate;

		std::vector<IDObject<VertexAttributeDescriptionData>> vertexAttributes;

		VertexBindingDescriptionData();

		bool operator==(const VertexBindingDescriptionData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const VertexBindingDescriptionData& rhs) const noexcept = default;
	};
}