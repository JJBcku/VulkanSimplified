#include "VSSharedNIpch.h"
#include "VSVertexBindingDescriptionData.h"

namespace VulkanSimplifiedInternal
{
	VertexBindingDescriptionData::VertexBindingDescriptionData()
	{
		stride = std::numeric_limits<std::uint32_t>::max();
		inputRate = static_cast<VkVertexInputRate>(std::numeric_limits<std::uint32_t>::max());
	}
}