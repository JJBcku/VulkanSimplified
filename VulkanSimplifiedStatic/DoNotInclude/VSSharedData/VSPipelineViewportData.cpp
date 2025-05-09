#include "VSSharedNIpch.h"
#include "VSPipelineViewportData.h"

namespace VulkanSimplifiedInternal
{
	PipelineViewportData::PipelineViewportData()
	{
		startX = std::numeric_limits<float>::max();
		startY = std::numeric_limits<float>::max();
		width = 0.0f;
		height = 0.0f;
		minDepth = std::numeric_limits<float>::max();
		maxDepth = std::numeric_limits<float>::lowest();
	}
}