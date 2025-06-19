#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupVertexBuffer.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupVertexBuffer::AutoCleanupVertexBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupVertexBuffer::~AutoCleanupVertexBuffer()
	{
	}

}