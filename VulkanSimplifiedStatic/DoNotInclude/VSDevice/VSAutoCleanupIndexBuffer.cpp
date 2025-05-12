#include "VSDeviceNIpch.h"
#include "VSAutoCleanupIndexBuffer.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupIndexBuffer::AutoCleanupIndexBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupIndexBuffer::~AutoCleanupIndexBuffer()
	{
	}

}