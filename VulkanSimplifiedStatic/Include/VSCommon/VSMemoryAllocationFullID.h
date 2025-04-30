#pragma once

template<class T>
class IDObject;

namespace VulkanSimplifiedInternal
{
	class MemoryAllocationData;
}

namespace VulkanSimplified
{
	typedef size_t MemoryTypeIndex;
	typedef std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, MemoryTypeIndex> MemoryAllocationFullID;
}