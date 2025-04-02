#include "VSSharedNIpch.h"
#include "VSPushConstantData.h"

namespace VulkanSimplifiedInternal
{
	PushConstantData::PushConstantData()
	{
		shaderStages = static_cast<VkShaderStageFlags>(0);
		offset = std::numeric_limits<std::uint32_t>::max();
		size = std::numeric_limits<std::uint32_t>::max();
		padding = 0;
	}
}