#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSDevice/VSDataBufferListsDef.h"
#include "../../Include/VSDevice/VSIndexTypeDef.h"

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
		IDObject<AutoCleanupIndexBuffer> AddIndexBuffer(size_t indicesCount, VulkanSimplified::IndexType indexType, const std::vector<size_t>& queuesUsingBuffer,
			size_t addOnReserving);
		IDObject<AutoCleanupUniformBuffer> AddUniformBuffer(VulkanSimplified::MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving);

		void BindVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);

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
		VulkanSimplified::MemorySize GetVertexBuffersSize(IDObject<AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersRequiredAligment(IDObject<AutoCleanupVertexBuffer> bufferID) const;

		uint32_t GetStagingBuffersMemoryTypeMask(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetStagingBuffersSize(IDObject<AutoCleanupStagingBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetStagingBuffersRequiredAligment(IDObject<AutoCleanupStagingBuffer> bufferID) const;

		uint32_t GetIndexBuffersMemoryTypeMask(IDObject<AutoCleanupIndexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetIndexBuffersSize(IDObject<AutoCleanupIndexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetIndexBuffersRequiredAligment(IDObject<AutoCleanupIndexBuffer> bufferID) const;

		uint32_t GetUniformBuffersMemoryTypeMask(IDObject<AutoCleanupUniformBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetUniformBuffersSize(IDObject<AutoCleanupUniformBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetUniformBuffersRequiredAligment(IDObject<AutoCleanupUniformBuffer> bufferID) const;

		void WriteToVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize dataSize);
		void WriteToStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize dataSize);
		void WriteToIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize dataSize);
		void WriteToUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize dataSize);

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