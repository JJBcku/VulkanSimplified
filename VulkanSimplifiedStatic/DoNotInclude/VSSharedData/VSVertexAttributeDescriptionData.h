#pragma once

namespace VulkanSimplifiedInternal
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