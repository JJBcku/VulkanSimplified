#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "VSMemoryAllocationData.h"

#include "../../../Include/VSCommon/VSMemorySizeDef.h"
#include "../../../Include/VSCommon/VSMemoryTypeData.h"
#include "../../../Include/VSCommon/VSMemorySuballocationFullID.h"

#include <stdint.h>

typedef struct VkDevice_T* VkDevice;
typedef struct VkDeviceMemory_T* VkDeviceMemory;
typedef struct VkImage_T* VkImage;
typedef struct VkBuffer_T* VkBuffer;

namespace VulkanSimplified
{
	class MemoryTypeInternalData
	{
	public:
		MemoryTypeInternalData(VkDevice device, uint32_t heapIndex, const MemoryTypeData& memoryData, size_t reservedAllocation);
		~MemoryTypeInternalData();

		MemoryTypeInternalData(const MemoryTypeInternalData&) noexcept = delete;
		MemoryTypeInternalData(MemoryTypeInternalData&& rhs) noexcept;

		MemoryTypeInternalData& operator=(const MemoryTypeInternalData&) noexcept = delete;
		MemoryTypeInternalData& operator=(MemoryTypeInternalData&& rhs) noexcept;

		IDObject<MemoryAllocationData> AddMemoryAllocation(size_t dataSize, size_t initialSuballocationsReserved, size_t addOnReserving);

		VkDeviceMemory GetMemory(IDObject<MemoryAllocationData> memoryId) const;

		bool FreeMemory(IDObject<MemoryAllocationData> memoryId, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty);

		uint32_t GetHeapIndex() const;
		uint32_t GetTypeIndex() const;
		MemoryTypeProperties GetProperties() const;

		size_t GetMemoryAllocationsSize(IDObject<MemoryAllocationData> allocationID) const;

		size_t BindImage(IDObject<MemoryAllocationData> allocationID, VkImage image, MemorySize size, MemorySize aligment, size_t addOnReserving);
		size_t BindBuffer(IDObject<MemoryAllocationData> allocationID, VkBuffer buffer, MemorySize size, MemorySize aligment, size_t addOnReserving);

		bool CheckForAllocationsExistence(IDObject<MemoryAllocationData> allocationID);
		bool RemoveSuballocation(IDObject<MemoryAllocationData> allocationID, size_t beggining, bool throwOnNotFound);

		void WriteToMemory(MemorySuballocationFullID suballocationID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize writeSize);

		bool IsMemoryMapped() const;

	private:
		VkDevice _device;

		uint32_t _heapIndex;
		uint32_t _typeIndex;
		MemoryTypeProperties _properties;

		UnsortedIDVector<MemoryAllocationData> _allocationsList;
	};
}