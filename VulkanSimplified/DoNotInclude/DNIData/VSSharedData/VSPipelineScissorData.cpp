#include "VSSharedNIpch.h"
#include "VSPipelineScissorData.h"

namespace VulkanSimplified
{
	PipelineScissorData::PipelineScissorData()
	{
		offsetX = std::numeric_limits<int32_t>::max();
		offsetY = std::numeric_limits<int32_t>::max();
		width = std::numeric_limits<uint32_t>::max();
		height = std::numeric_limits<uint32_t>::max();
	}
}
