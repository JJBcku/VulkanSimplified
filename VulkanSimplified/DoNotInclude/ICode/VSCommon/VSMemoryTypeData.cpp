#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSMemoryTypeData.h"

namespace VulkanSimplified
{
	MemoryTypeData::MemoryTypeData()
	{
		memoryIndex = std::numeric_limits<uint32_t>::max();
		properties = std::numeric_limits<MemoryTypeProperties>::max();
	}
}