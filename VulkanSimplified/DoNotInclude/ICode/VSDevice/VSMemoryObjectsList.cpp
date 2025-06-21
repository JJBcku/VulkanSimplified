#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSMemoryObjectsList.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSMemoryObjectsListInternal.h"

namespace VulkanSimplified
{
	MemoryObjectsList::MemoryObjectsList(MemoryObjectsListInternal& ref) : _internal(ref)
	{
	}

	MemoryObjectsList::~MemoryObjectsList()
	{
	}

	MemoryAllocationFullID MemoryObjectsList::AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving)
	{
		return _internal.AllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserving);
	}

	std::optional<MemoryAllocationFullID> MemoryObjectsList::TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving)
	{
		return _internal.TryToAllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserving);
	}

	bool MemoryObjectsList::FreeMemory(MemoryAllocationFullID memoryID, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty)
	{
		return _internal.FreeMemory(memoryID, throwOnIDNotFound, throwOnSuballocationsNotEmpty);
	}

	bool MemoryObjectsList::IsMemoryMapped(MemoryAllocationFullID allocationID) const
	{
		return _internal.IsMemoryMapped(allocationID);
	}

}