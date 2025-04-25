#pragma once

namespace VulkanSimplifiedInternal
{
	class MemoryAllocationData;
}

namespace VulkanSimplified
{
	typedef std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, size_t> AllocationFullID;
}