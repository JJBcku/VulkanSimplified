#include "VSSharedDNIpch.h"
#include "VSSubpassDependencyData.h"

namespace VulkanSimplified
{
	SubpassDependencyData::SubpassDependencyData()
	{
		srcSubpass = static_cast<uint32_t>(std::numeric_limits<int32_t>::max());
		dstSubpass = static_cast<uint32_t>(std::numeric_limits<int32_t>::max());
		srcStageFlags = 0;
		dstStageFlags = 0;
		srcAccessFlags = VK_ACCESS_FLAG_BITS_MAX_ENUM;
		dstAccessFlags = VK_ACCESS_FLAG_BITS_MAX_ENUM;
	}
}