#include "VSCommonIpch.h"
#include "VSMemoryHeapData.h"

namespace VulkanSimplified
{
	MemoryHeapData::MemoryHeapData() : memoryTypes()
	{
		size = 0;
		properties = std::numeric_limits<MemoryHeapProperties>::max();

		memoryTypeAmount = 0;
		std::memset(memoryTypes.data(), 0, sizeof(memoryTypes[0]) * memoryTypes.size());
	}
}