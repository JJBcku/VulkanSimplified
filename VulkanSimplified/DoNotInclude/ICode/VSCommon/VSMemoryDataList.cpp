#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSMemoryDataList.h"

namespace VulkanSimplified
{
	MemoryDataList::MemoryDataList() : heapAmount(0), memoryHeaps()
	{
		std::memset(memoryHeaps.data(), 0, sizeof(memoryHeaps[0]) * memoryHeaps.size());
	}
}