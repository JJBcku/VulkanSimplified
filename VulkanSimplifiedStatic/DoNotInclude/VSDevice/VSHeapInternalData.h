#pragma once

#include "../../Include/VSCommon/VSMemorySizeDef.h"
#include "../../Include/VSCommon/VSMemoryHeapPropertiesDef.h"

namespace VulkanSimplifiedInternal
{
	struct HeapInternalData
	{
		VulkanSimplified::MemorySize heapSize;
		VulkanSimplified::MemorySize usedSize;
		VulkanSimplified::MemoryHeapProperties properties;

		HeapInternalData();

		VulkanSimplified::MemorySize GetFreeSize() const;
	};
}