#pragma once

#include <CustomLists\IDObjectDef.h>

#include "VSMemoryObjectsListDef.h"

namespace VulkanSimplifiedInternal
{
	class MemoryObjectsListInternal;
}

namespace VulkanSimplified
{
	class MemoryObjectsList
	{
	public:
		MemoryObjectsList(VulkanSimplifiedInternal::MemoryObjectsListInternal& ref);
		~MemoryObjectsList();

		MemoryAllocationFullID AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved, const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties,
			std::uint32_t memoryTypeMask = std::numeric_limits<std::uint32_t>::max(), size_t addOnReserving = 0);

		std::optional<MemoryAllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask = std::numeric_limits<std::uint32_t>::max(), size_t addOnReserving = 0);

		bool FreeMemory(std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound = true);

		bool IsMemoryMapped(VulkanSimplified::MemoryAllocationFullID allocationID) const;

	private:
		VulkanSimplifiedInternal::MemoryObjectsListInternal& _internal;
	};
}