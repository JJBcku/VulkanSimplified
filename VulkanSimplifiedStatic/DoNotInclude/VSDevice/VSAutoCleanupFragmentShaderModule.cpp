#include "VSDeviceNIpch.h"
#include "VSAutoCleanupFragmentShaderModule.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupFragmentShaderModule::AutoCleanupFragmentShaderModule(VkDevice device, VkShaderModule shader) : AutoCleanupShaderModule(device, shader)
	{
	}

	AutoCleanupFragmentShaderModule::~AutoCleanupFragmentShaderModule()
	{
	}

}