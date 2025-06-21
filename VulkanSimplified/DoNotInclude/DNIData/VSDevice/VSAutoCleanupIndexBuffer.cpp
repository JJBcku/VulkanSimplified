#include "VSDeviceNIpch.h"
#include "VSAutoCleanupIndexBuffer.h"

namespace VulkanSimplified
{
	AutoCleanupIndexBuffer::AutoCleanupIndexBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupIndexBuffer::~AutoCleanupIndexBuffer()
	{
	}

}