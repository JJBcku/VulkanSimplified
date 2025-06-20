#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupStagingBuffer.h"

namespace VulkanSimplified
{
	AutoCleanupStagingBuffer::AutoCleanupStagingBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupStagingBuffer::~AutoCleanupStagingBuffer()
	{
	}


}