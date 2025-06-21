#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupVertexBuffer.h"

namespace VulkanSimplified
{
	AutoCleanupVertexBuffer::AutoCleanupVertexBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupVertexBuffer::~AutoCleanupVertexBuffer()
	{
	}

}