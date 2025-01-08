#include "VSCommonIpch.h"
#include "VSMemoryData.h"

namespace VulkanSimplified
{

	MemoryTypeData::MemoryTypeData()
	{
		memoryIndex = std::numeric_limits<size_t>::max();
		properties = std::numeric_limits<MemoryTypeProperties>::max();
	}

	MemoryHeapData::MemoryHeapData() : memoryTypes()
	{
		size = 0;
		properties = std::numeric_limits<MemoryHeapProperties>::max();

		memoryTypeAmount = 0;
	}

	MemoryDataList::MemoryDataList() : heapAmount(0), memoryHeaps()
	{
	}

}