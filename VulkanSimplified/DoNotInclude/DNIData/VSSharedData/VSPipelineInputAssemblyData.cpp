#include "VSSharedDNIpch.h"
#include "VSPipelineInputAssemblyData.h"

namespace VulkanSimplified
{
	PipelineInputAssemblyData::PipelineInputAssemblyData()
	{
		topology = VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
		primitiveRestartEnable = static_cast<VkBool32>(std::numeric_limits<uint32_t>::max());
	}
}