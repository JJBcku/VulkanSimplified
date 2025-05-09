#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "VSMemoryAllocationData.h"

#include "../../Include/VSCommon/VSMemorySizeDef.h"
#include "../../Include/VSCommon/VSMemoryTypeData.h"

namespace VulkanSimplifiedInternal
{
	class MemoryTypeInternalData
	{
	public:
		MemoryTypeInternalData(VkDevice device, uint32_t heapIndex, const VulkanSimplified::MemoryTypeData& memoryData, size_t reservedAllocation);
		~MemoryTypeInternalData();

		MemoryTypeInternalData(const MemoryTypeInternalData&) noexcept = delete;
		MemoryTypeInternalData(MemoryTypeInternalData&& rhs) noexcept;

		MemoryTypeInternalData& operator=(const MemoryTypeInternalData&) noexcept = delete;
		MemoryTypeInternalData& operator=(MemoryTypeInternalData&& rhs) noexcept;

		IDObject<MemoryAllocationData> AddMemoryAllocation(size_t dataSize, size_t initialSuballocationsReserved, size_t addOnReserving);

		bool FreeMemory(IDObject<MemoryAllocationData> memoryId, bool throwOnNotFound);

		uint32_t GetHeapIndex() const;
		uint32_t GetTypeIndex() const;
		VulkanSimplified::MemoryTypeProperties GetProperties() const;

		size_t GetMemoryAllocationsSize(IDObject<MemoryAllocationData> allocationID) const;

		size_t BindImage(IDObject<MemoryAllocationData> allocationID, VkImage image, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment, size_t addOnReserving);
		size_t BindBuffer(IDObject<MemoryAllocationData> allocationID, VkBuffer buffer, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment, size_t addOnReserving);

		bool CheckForAllocationsExistence(IDObject<MemoryAllocationData> allocationID);
		bool RemoveSuballocation(IDObject<MemoryAllocationData> allocationID, size_t beggining, bool throwOnNotFound);

	private:
		VkDevice _device;

		uint32_t _heapIndex;
		uint32_t _typeIndex;
		VulkanSimplified::MemoryTypeProperties _properties;

		UnsortedIDVector<MemoryAllocationData> _allocationsList;
	};
}