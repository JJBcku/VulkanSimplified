#pragma once

namespace VulkanSimplifiedInternal
{
	struct PipelineRasterizationData
	{
		VkPolygonMode polygonMode;
		VkCullModeFlagBits cullMode;
		VkFrontFace frontFace;
		uint32_t padding;

		PipelineRasterizationData();

		bool operator==(const PipelineRasterizationData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const PipelineRasterizationData& rhs) const noexcept = default;
	};
}