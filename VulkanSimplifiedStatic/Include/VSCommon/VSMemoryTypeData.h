#pragma once

#include "VSMemoryTypePropertiesDef.h"

namespace VulkanSimplified
{
	struct MemoryTypeData
	{
		size_t memoryIndex;
		MemoryTypeProperties properties;

		MemoryTypeData();
	};
}