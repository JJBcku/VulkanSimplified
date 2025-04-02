#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	struct VertexAttributeDescriptionData;

	struct VertexBindingDescriptionData
	{
		std::uint32_t stride;
		VkVertexInputRate inputRate;

		std::vector<IDObject<VertexAttributeDescriptionData>> vertexAttributes;

		VertexBindingDescriptionData();

		bool operator==(const VertexBindingDescriptionData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const VertexBindingDescriptionData& rhs) const noexcept = default;
	};
}