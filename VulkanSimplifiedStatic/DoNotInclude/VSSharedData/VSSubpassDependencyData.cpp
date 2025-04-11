#include "VSSharedNIpch.h"
#include "VSSubpassDependencyData.h"

namespace VulkanSimplifiedInternal
{
	SubpassDependencyData::SubpassDependencyData()
	{
		srcSubpass = static_cast<uint32_t>(std::numeric_limits<int32_t>::max());
		dstSubpass = static_cast<uint32_t>(std::numeric_limits<int32_t>::max());
		srcStageFlags = 0;
		dstStageFlags = 0;
		srcAccessFlags = 0;
		dstAccessFlags = 0;
	}
}