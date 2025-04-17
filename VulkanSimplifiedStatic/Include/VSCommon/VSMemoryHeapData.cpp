#include "VSCommonIpch.h"
#include "VSMemoryHeapData.h"

namespace VulkanSimplified
{
	MemoryHeapData::MemoryHeapData() : memoryTypes()
	{
		size = 0;
		properties = std::numeric_limits<MemoryHeapProperties>::max();

		memoryTypeAmount = 0;
	}
}