#include "VSSharedNIpch.h"
#include "VSPipelineRasterizationData.h"

namespace VulkanSimplifiedInternal
{
	PipelineRasterizationData::PipelineRasterizationData()
	{
		polygonMode = VK_POLYGON_MODE_MAX_ENUM;
		cullMode = VK_CULL_MODE_FLAG_BITS_MAX_ENUM;
		frontFace = VK_FRONT_FACE_MAX_ENUM;
		padding = 0;
	}
}