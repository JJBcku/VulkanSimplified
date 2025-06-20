#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupFragmentShaderModule.h"

namespace VulkanSimplified
{
	AutoCleanupFragmentShaderModule::AutoCleanupFragmentShaderModule(VkDevice device, VkShaderModule shader) : AutoCleanupShaderModule(device, shader)
	{
	}

	AutoCleanupFragmentShaderModule::~AutoCleanupFragmentShaderModule()
	{
	}

}