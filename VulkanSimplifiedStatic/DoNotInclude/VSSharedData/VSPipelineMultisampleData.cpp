#include "VSSharedNIpch.h"
#include "VSPipelineMultisampleData.h"

namespace VulkanSimplifiedInternal
{
	PipelineMultisampleData::PipelineMultisampleData()
	{
		sampleCount = static_cast<VkSampleCountFlagBits>(0);
		sampleShadingEnable = static_cast<VkBool32>(std::numeric_limits<uint32_t>::max());
		minSampleShading = std::numeric_limits<float>::max();
		padding = 0;
	}
}