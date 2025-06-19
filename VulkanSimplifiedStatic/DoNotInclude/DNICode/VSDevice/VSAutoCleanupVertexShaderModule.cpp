#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupVertexShaderModule::AutoCleanupVertexShaderModule(VkDevice device, VkShaderModule shader) : AutoCleanupShaderModule(device, shader)
	{
	}

	AutoCleanupVertexShaderModule::~AutoCleanupVertexShaderModule()
	{
	}

}