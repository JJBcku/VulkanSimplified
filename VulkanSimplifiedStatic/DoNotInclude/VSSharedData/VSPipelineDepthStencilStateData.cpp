#include "VSSharedNIpch.h"
#include "VSPipelineDepthStencilStateData.h"

namespace VulkanSimplifiedInternal
{
	PipelineDepthStencilStateData::PipelineDepthStencilStateData()
	{
		depthTestEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
		depthWriteEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
		compareOp = static_cast<VkCompareOp>(std::numeric_limits<std::uint32_t>::max());
		minDepth = std::numeric_limits<float>::max();
		maxDepth = std::numeric_limits<float>::lowest();
		padding = 0;
	}
}