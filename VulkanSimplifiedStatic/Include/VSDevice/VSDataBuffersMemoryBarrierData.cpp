#include "VSDeviceIpch.h"
#include "VSDataBuffersMemoryBarrierData.h"

namespace VulkanSimplified
{
	DataBuffersMemoryBarrierData::DataBuffersMemoryBarrierData()
	{
		srcAccess = 0;
		dstAccess = 0;
	}
}