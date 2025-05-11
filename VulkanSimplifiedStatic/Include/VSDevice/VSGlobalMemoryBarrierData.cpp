#include "VSDeviceIpch.h"
#include "VSGlobalMemoryBarrierData.h"

namespace VulkanSimplified
{
	GlobalMemoryBarrierData::GlobalMemoryBarrierData()
	{
		srcAccess = 0;
		dstAccess = 0;
	}
}