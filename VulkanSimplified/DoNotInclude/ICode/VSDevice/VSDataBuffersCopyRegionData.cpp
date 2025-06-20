#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDataBuffersCopyRegionData.h"

namespace VulkanSimplified
{
	DataBuffersCopyRegionData::DataBuffersCopyRegionData()
	{
		srcOffset = std::numeric_limits<MemorySize>::max();
		dstOffset = std::numeric_limits<MemorySize>::max();
		writeSize = std::numeric_limits<MemorySize>::max();
	}
}