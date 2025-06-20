#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplified
{
	AutoCleanupVertexShaderModule::AutoCleanupVertexShaderModule(VkDevice device, VkShaderModule shader) : AutoCleanupShaderModule(device, shader)
	{
	}

	AutoCleanupVertexShaderModule::~AutoCleanupVertexShaderModule()
	{
	}

}