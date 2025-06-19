#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSGlobalMemoryBarrierData.h"

namespace VulkanSimplified
{
	GlobalMemoryBarrierData::GlobalMemoryBarrierData()
	{
		srcAccess = 0;
		dstAccess = 0;
	}
}