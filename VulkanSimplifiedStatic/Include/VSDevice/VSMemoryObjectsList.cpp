#include "VSDeviceIpch.h"
#include "VSMemoryObjectsList.h"

#include "../../DoNotInclude/VSDevice/VSMemoryObjectsListInternal.h"

namespace VulkanSimplified
{
	MemoryObjectsList::MemoryObjectsList(VulkanSimplifiedInternal::MemoryObjectsListInternal& ref) : _internal(ref)
	{
	}

	MemoryObjectsList::~MemoryObjectsList()
	{
	}

	AllocationFullID MemoryObjectsList::AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve)
	{
		return _internal.AllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserve);
	}

	std::optional<AllocationFullID> MemoryObjectsList::TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve)
	{
		return _internal.TryToAllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserve);
	}

	bool MemoryObjectsList::FreeMemory(std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound)
	{
		return _internal.FreeMemory(memoryID, throwOnNotFound);
	}
}