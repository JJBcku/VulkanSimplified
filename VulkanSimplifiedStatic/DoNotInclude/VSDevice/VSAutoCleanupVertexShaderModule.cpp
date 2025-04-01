#include "VSDeviceNIpch.h"
#include "VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupVertexShaderModule::AutoCleanupVertexShaderModule(VkDevice device, VkShaderModule shader) : AutoCleanupShaderModule(device, shader)
	{
	}

	AutoCleanupVertexShaderModule::~AutoCleanupVertexShaderModule()
	{
	}

}