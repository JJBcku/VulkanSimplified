#include "VSCommonIpch.h"
#include "VSMemoryTypeData.h"

namespace VulkanSimplified
{
	MemoryTypeData::MemoryTypeData()
	{
		memoryIndex = std::numeric_limits<size_t>::max();
		properties = std::numeric_limits<MemoryTypeProperties>::max();
	}
}