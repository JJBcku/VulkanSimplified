#pragma once

#include <CustomLists\IDObjectDef.h>

#include "VSMemoryObjectsListDef.h"

#include <limits>
#include <stdint.h>
#include <vector>
#include <optional>

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
			uint32_t memoryTypeMask = std::numeric_limits<uint32_t>::max(), size_t addOnReserving = 0);

		std::optional<MemoryAllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask = std::numeric_limits<uint32_t>::max(), size_t addOnReserving = 0);

		bool FreeMemory(VulkanSimplified::MemoryAllocationFullID memoryID, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty);

		bool IsMemoryMapped(VulkanSimplified::MemoryAllocationFullID allocationID) const;

	private:
		VulkanSimplifiedInternal::MemoryObjectsListInternal& _internal;
	};
}