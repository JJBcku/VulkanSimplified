#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupUniformBuffer.h"

namespace VulkanSimplified
{
	AutoCleanupUniformBuffer::AutoCleanupUniformBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupUniformBuffer::~AutoCleanupUniformBuffer()
	{
	}

}