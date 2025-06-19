#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSSuballocationInternalData.h"

namespace VulkanSimplifiedInternal
{
	SuballocationInternalData::SuballocationInternalData()
	{
		beggining = std::numeric_limits<size_t>::max();
		size = 0;
	}
}