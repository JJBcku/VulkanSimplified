#include "VSSharedNIpch.h"
#include "../../DNIHeaders/VSSharedData/VSSharedShaderPipelineData.h"

namespace VulkanSimplifiedInternal
{
	SharedShaderPipelineData::SharedShaderPipelineData()
	{
		shaderStage = static_cast<VkShaderStageFlagBits>(0);
		padding = 0;
		entryPointName = "Unset";
	}
}