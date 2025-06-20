#pragma once

#include "../../../Include/VSCommon/VSMemorySizeDef.h"
#include "../../../Include/VSCommon/VSMemoryHeapPropertiesDef.h"

namespace VulkanSimplified
{
	struct HeapInternalData
	{
		MemorySize heapSize;
		MemorySize usedSize;
		MemoryHeapProperties properties;

		HeapInternalData();

		MemorySize GetFreeSize() const;
	};
}