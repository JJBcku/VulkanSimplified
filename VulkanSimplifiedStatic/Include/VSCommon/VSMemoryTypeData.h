#pragma once

#include "VSMemoryTypePropertiesDef.h"

namespace VulkanSimplified
{
	struct MemoryTypeData
	{
		uint32_t memoryIndex;
		MemoryTypeProperties properties;

		MemoryTypeData();
	};
}