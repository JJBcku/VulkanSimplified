#include "VSSharedDNIpch.h"
#include "VSVertexAttributeDescriptionData.h"

namespace VulkanSimplified
{
	VertexAttributeDescriptionData::VertexAttributeDescriptionData()
	{
		format = VK_FORMAT_MAX_ENUM;
		offset = std::numeric_limits<uint32_t>::max();
	}
}