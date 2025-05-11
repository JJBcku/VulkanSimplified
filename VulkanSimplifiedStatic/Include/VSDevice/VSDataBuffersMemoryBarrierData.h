#pragma once

#include "VSQueueOwnershipTransferData.h"

#include "../VSCommon/VSAccessFlagsDef.h"
#include "../VSCommon/VSDataBuffersGenericID.h"

namespace VulkanSimplified
{
	struct DataBuffersMemoryBarrierData
	{
		AccessFlags srcAccess;
		AccessFlags dstAccess;
		std::optional<QueueOwnershipTransferData> queueData;
		DataBuffersGenericID bufferID;

		DataBuffersMemoryBarrierData();
	};
}