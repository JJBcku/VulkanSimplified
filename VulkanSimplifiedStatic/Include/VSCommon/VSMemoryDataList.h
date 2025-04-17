#pragma once

#include "VSMemoryHeapData.h"

namespace VulkanSimplified
{
	struct MemoryDataList
	{
		size_t heapAmount;
		std::array<MemoryHeapData, VK_MAX_MEMORY_HEAPS> memoryHeaps;

		MemoryDataList();
	};
}