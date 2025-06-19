#include "VSSharedNIpch.h"
#include "../../DNIHeaders/VSSharedData/VSVertexBindingDescriptionData.h"

namespace VulkanSimplifiedInternal
{
	VertexBindingDescriptionData::VertexBindingDescriptionData()
	{
		stride = std::numeric_limits<uint32_t>::max();
		inputRate = static_cast<VkVertexInputRate>(std::numeric_limits<uint32_t>::max());
	}
}