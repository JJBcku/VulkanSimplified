#include "VSDeviceNIpch.h"
#include "VSAutoCleanupStagingBuffer.h"

namespace VulkanSimplified
{
	AutoCleanupStagingBuffer::AutoCleanupStagingBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupStagingBuffer::~AutoCleanupStagingBuffer()
	{
	}


}