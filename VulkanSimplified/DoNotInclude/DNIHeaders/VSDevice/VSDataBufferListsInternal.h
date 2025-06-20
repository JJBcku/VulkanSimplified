#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../../Include/VSDevice/VSDataBufferListsDef.h"
#include "../../../Include/VSDevice/VSIndexTypeDef.h"

#include "../../../Include/VSCommon/VSMemoryAllocationFullID.h"
#include "../../../Include/VSCommon/VSMemorySizeDef.h"

#include <stdint.h>

typedef struct VkDevice_T* VkDevice;
typedef struct VkBuffer_T* VkBuffer;

namespace VulkanSimplified
{
	struct DataBufferListsInitialCapacities;
}

namespace VulkanSimplified
{
	class DeviceCoreInternal;
	class MemoryObjectsListInternal;

	class DataBufferListsInternal
	{
	public:
		DataBufferListsInternal(const DeviceCoreInternal& deviceCore, MemoryObjectsListInternal& memoryObjectsList, VkDevice device,
			const DataBufferListsInitialCapacities& initialCapacities);
		~DataBufferListsInternal();

		IDObject<AutoCleanupVertexBuffer> AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving);
		IDObject<AutoCleanupStagingBuffer> AddStagingBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving);
		IDObject<AutoCleanupIndexBuffer> AddIndexBuffer(size_t indicesCount, IndexType indexType, const std::vector<size_t>& queuesUsingBuffer,
			size_t addOnReserving);
		IDObject<AutoCleanupUniformBuffer> AddUniformBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving);

		void BindVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving);

		VkBuffer GetVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		VkBuffer GetStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		VkBuffer GetIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID) const;
		VkBuffer GetUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID) const;

		const AutoCleanupVertexBuffer& GetVertexBufferInternal(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		const AutoCleanupStagingBuffer& GetStagingBufferInternal(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		const AutoCleanupIndexBuffer& GetIndexBufferInternal(IDObject<AutoCleanupIndexBuffer> bufferID) const;
		const AutoCleanupUniformBuffer& GetUniformBufferInternal(IDObject<AutoCleanupUniformBuffer> bufferID) const;

		bool RemoveVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, bool throwOnIDNotFound);
		bool RemoveStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, bool throwOnIDNotFound);
		bool RemoveIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, bool throwOnIDNotFound);
		bool RemoveUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, bool throwOnIDNotFound);

		uint32_t GetVertexBuffersMemoryTypeMask(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		MemorySize GetVertexBuffersSize(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		MemorySize GetVertexBuffersRequiredAligment(IDObject<AutoCleanupVertexBuffer> bufferID) const;

		uint32_t GetStagingBuffersMemoryTypeMask(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		MemorySize GetStagingBuffersSize(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		MemorySize GetStagingBuffersRequiredAligment(IDObject<AutoCleanupStagingBuffer> bufferID) const;

		uint32_t GetIndexBuffersMemoryTypeMask(IDObject<AutoCleanupIndexBuffer> bufferID) const;
		MemorySize GetIndexBuffersSize(IDObject<AutoCleanupIndexBuffer> bufferID) const;
		MemorySize GetIndexBuffersRequiredAligment(IDObject<AutoCleanupIndexBuffer> bufferID) const;

		uint32_t GetUniformBuffersMemoryTypeMask(IDObject<AutoCleanupUniformBuffer> bufferID) const;
		MemorySize GetUniformBuffersSize(IDObject<AutoCleanupUniformBuffer> bufferID) const;
		MemorySize GetUniformBuffersRequiredAligment(IDObject<AutoCleanupUniformBuffer> bufferID) const;

		void WriteToVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);
		void WriteToStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);
		void WriteToIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);
		void WriteToUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);

	private:
		const DeviceCoreInternal& _deviceCore;
		MemoryObjectsListInternal& _memoryObjectsList;

		VkDevice _device;

		UnsortedIDVector<AutoCleanupVertexBuffer> _vertexBuffers;
		UnsortedIDVector<AutoCleanupStagingBuffer> _stagingBuffers;
		UnsortedIDVector<AutoCleanupIndexBuffer> _indexBuffers;
		UnsortedIDVector<AutoCleanupUniformBuffer> _uniformBuffers;
	};
}