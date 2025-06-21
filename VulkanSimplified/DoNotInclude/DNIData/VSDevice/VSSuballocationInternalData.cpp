#include "VSDeviceDNIpch.h"
#include "VSSuballocationInternalData.h"

namespace VulkanSimplified
{
	SuballocationInternalData::SuballocationInternalData()
	{
		beggining = std::numeric_limits<size_t>::max();
		size = 0;
	}
}