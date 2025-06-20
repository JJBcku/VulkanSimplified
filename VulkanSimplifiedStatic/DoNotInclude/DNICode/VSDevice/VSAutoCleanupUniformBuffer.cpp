#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupUniformBuffer.h"

namespace VulkanSimplified
{
	AutoCleanupUniformBuffer::AutoCleanupUniformBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupUniformBuffer::~AutoCleanupUniformBuffer()
	{
	}

}