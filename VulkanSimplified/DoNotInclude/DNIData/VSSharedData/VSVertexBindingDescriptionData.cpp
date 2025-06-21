#include "VSSharedDNIpch.h"
#include "VSVertexBindingDescriptionData.h"

namespace VulkanSimplified
{
	VertexBindingDescriptionData::VertexBindingDescriptionData()
	{
		stride = std::numeric_limits<uint32_t>::max();
		inputRate = static_cast<VkVertexInputRate>(std::numeric_limits<uint32_t>::max());
	}
}