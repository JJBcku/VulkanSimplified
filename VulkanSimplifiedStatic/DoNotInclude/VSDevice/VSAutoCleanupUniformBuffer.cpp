#include "VSDeviceNIpch.h"
#include "VSAutoCleanupUniformBuffer.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupUniformBuffer::AutoCleanupUniformBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupUniformBuffer::~AutoCleanupUniformBuffer()
	{
	}

}