#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplified
{
	AutoCleanupVertexShaderModule::AutoCleanupVertexShaderModule(VkDevice device, VkShaderModule shader) : AutoCleanupShaderModule(device, shader)
	{
	}

	AutoCleanupVertexShaderModule::~AutoCleanupVertexShaderModule()
	{
	}

}