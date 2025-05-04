#pragma once

#include <CustomLists\IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class MemoryAllocationData;
}

namespace VulkanSimplified
{
	typedef size_t MemoryTypeIndex;
	typedef std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, MemoryTypeIndex> MemoryAllocationFullID;
}