#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSQueueOwnershipTransferData.h"

namespace VulkanSimplified
{
	QueueOwnershipTransferData::QueueOwnershipTransferData()
	{
		srcQueueIndex = std::numeric_limits<size_t>::max();
		dstQueueIndex = std::numeric_limits<size_t>::max();
	}

	QueueOwnershipTransferData::QueueOwnershipTransferData(size_t srcQueue, size_t dstQueue) : srcQueueIndex(srcQueue), dstQueueIndex(dstQueue)
	{
	}
}