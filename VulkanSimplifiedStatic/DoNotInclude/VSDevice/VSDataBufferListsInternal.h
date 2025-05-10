#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSDevice/VSDataBufferListsDef.h"
#include "../../Include/VSCommon/VSMemoryAllocationFullID.h"
#include "../../Include/VSCommon/VSMemorySizeDef.h"

namespace VulkanSimplified
{
	struct DataBufferListsInitialCapacities;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
	class MemoryObjectsListInternal;

	class DataBufferListsInternal
	{
	public:
		DataBufferListsInternal(const DeviceCoreInternal& deviceCore, MemoryObjectsListInternal& memoryObjectsList, VkDevice device,
			const VulkanSimplified::DataBufferListsInitialCapacities& initialCapacities);
		~DataBufferListsInternal();

		IDObject<AutoCleanupVertexBuffer> AddVertexBuffer(VulkanSimplified::MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving);
		IDObject<AutoCleanupStagingBuffer> AddStagingBuffer(VulkanSimplified::MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving);

		void BindVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);

		VkBuffer GetVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		VkBuffer GetStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID) const;

		uint32_t GetVertexBuffersMemoryTypeMask(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersSize(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersRequiredAligment(IDObject<AutoCleanupVertexBuffer> bufferID) const;

		uint32_t GetStagingBuffersMemoryTypeMask(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetStagingBuffersSize(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetStagingBuffersRequiredAligment(IDObject<AutoCleanupStagingBuffer> bufferID) const;

		void WriteToStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize dataSize);

	private:
		const DeviceCoreInternal& _deviceCore;
		MemoryObjectsListInternal& _memoryObjectsList;

		VkDevice _device;

		UnsortedIDVector<AutoCleanupVertexBuffer> _vertexBuffers;
		UnsortedIDVector<AutoCleanupStagingBuffer> _stagingBuffers;
	};
}