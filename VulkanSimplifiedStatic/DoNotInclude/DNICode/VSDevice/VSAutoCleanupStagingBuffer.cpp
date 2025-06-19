#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupStagingBuffer.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupStagingBuffer::AutoCleanupStagingBuffer(VkDevice device, VkBuffer buffer) : AutoCleanupDataBuffer(device, buffer)
	{
	}

	AutoCleanupStagingBuffer::~AutoCleanupStagingBuffer()
	{
	}


}