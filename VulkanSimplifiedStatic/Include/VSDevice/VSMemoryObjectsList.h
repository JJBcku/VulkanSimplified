#pragma once

template<class T>
class IDObject;

#include "../VSCommon/VSMemoryTypePropertiesDef.h"

#include "VSAllocationFullIDDef.h"

namespace VulkanSimplifiedInternal
{
	class MemoryObjectsListInternal;
	class MemoryAllocationData;
}

namespace VulkanSimplified
{
	class MemoryObjectsList
	{
	public:
		MemoryObjectsList(VulkanSimplifiedInternal::MemoryObjectsListInternal& ref);
		~MemoryObjectsList();

		AllocationFullID AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved, const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties,
			std::uint32_t memoryTypeMask = std::numeric_limits<std::uint32_t>::max(), size_t addOnReserve = 0);

		std::optional<AllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask = std::numeric_limits<std::uint32_t>::max(), size_t addOnReserve = 0);

		bool FreeMemory(std::pair<IDObject<VulkanSimplifiedInternal::MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound = true);

	private:
		VulkanSimplifiedInternal::MemoryObjectsListInternal& _internal;
	};
}