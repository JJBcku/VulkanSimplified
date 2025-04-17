#pragma once

#include "VSMemorySizeDef.h"
#include "VSMemoryHeapProperties.h"
#include "VSMemoryTypeData.h"

namespace VulkanSimplified
{
	struct MemoryHeapData
	{
		MemorySize size;
		MemoryHeapProperties properties;

		size_t memoryTypeAmount;
		std::array<MemoryTypeData, VK_MAX_MEMORY_TYPES> memoryTypes;

		MemoryHeapData();
	};
}