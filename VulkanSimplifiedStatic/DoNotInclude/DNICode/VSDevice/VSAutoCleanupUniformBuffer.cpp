#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupUniformBuffer.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupUniformBuffer::AutoCleanupUniformBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupUniformBuffer::~AutoCleanupUniformBuffer()
	{
	}

}