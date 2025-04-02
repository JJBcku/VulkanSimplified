#pragma once

namespace VulkanSimplifiedInternal
{
	struct PipelineViewportData
	{
		float startX;
		float startY;
		float width;
		float height;
		float minDepth;
		float maxDepth;

		PipelineViewportData();

		bool operator==(const PipelineViewportData& rhs) const noexcept = default;
		std::partial_ordering operator<=>(const PipelineViewportData& rhs) const noexcept = default;
	};
}