#include "VSSharedNIpch.h"
#include "VSPipelineInputAssemblyData.h"

namespace VulkanSimplifiedInternal
{
	PipelineInputAssemblyData::PipelineInputAssemblyData()
	{
		topology = VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
		primitiveRestartEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
	}
}