#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDataBuffersMemoryBarrierData.h"

namespace VulkanSimplified
{
	DataBuffersMemoryBarrierData::DataBuffersMemoryBarrierData()
	{
		srcAccess = 0;
		dstAccess = 0;
	}
}