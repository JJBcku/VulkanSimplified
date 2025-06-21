#include "VSSharedNIpch.h"
#include "VSPushConstantData.h"

namespace VulkanSimplified
{
	PushConstantData::PushConstantData()
	{
		shaderStages = static_cast<VkShaderStageFlags>(0);
		offset = std::numeric_limits<uint32_t>::max();
		size = std::numeric_limits<uint32_t>::max();
		padding = 0;
	}
}