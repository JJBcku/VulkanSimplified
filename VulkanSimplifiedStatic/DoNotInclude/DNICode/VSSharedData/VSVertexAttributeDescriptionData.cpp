#include "VSSharedNIpch.h"
#include "../../DNIHeaders/VSSharedData/VSVertexAttributeDescriptionData.h"

namespace VulkanSimplifiedInternal
{
	VertexAttributeDescriptionData::VertexAttributeDescriptionData()
	{
		format = VK_FORMAT_MAX_ENUM;
		offset = std::numeric_limits<uint32_t>::max();
	}
}