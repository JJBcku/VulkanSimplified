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

	MemoryAllocationFullID MemoryObjectsList::AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserving)
	{
		return _internal.AllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserving);
	}

	std::optional<MemoryAllocationFullID> MemoryObjectsList::TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserving)
	{
		return _internal.TryToAllocateMemory(memorySize, initialSuballocationsReserved, acceptableMemoryTypesProperties, memoryTypeMask, addOnReserving);
	}

	bool MemoryObjectsList::FreeMemory(std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound)
	{
		return _internal.FreeMemory(memoryID, throwOnNotFound);
	}

	bool MemoryObjectsList::IsMemoryMapped(VulkanSimplified::MemoryAllocationFullID allocationID) const
	{
		return _internal.IsMemoryMapped(allocationID);
	}

}