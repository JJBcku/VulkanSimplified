#pragma once

#include <vector>

#include "VSDataBufferListsDef.h"

#include "../VSCommon/VSMemorySizeDef.h"
#include "../VSCommon/VSMemoryAllocationFullID.h"

#include "VSIndexTypeDef.h"

namespace VulkanSimplifiedInternal
{
	class DataBufferListsInternal;
}

namespace VulkanSimplified
{
	class DataBufferLists
	{
	public:
		DataBufferLists(VulkanSimplifiedInternal::DataBufferListsInternal& ref);
		~DataBufferLists();

		DataBufferLists& operator=(const DataBufferLists& rhs) noexcept = delete;

		IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> AddStagingBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> AddIndexBuffer(size_t indicesCount, IndexType indexType,
			const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> AddUniformBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving = 0);

		void BindVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving = 0);
		void BindStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving = 0);
		void BindIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving = 0);
		void BindUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving = 0);

		bool RemoveVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, bool throwOnIDNotFound);
		bool RemoveStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, bool throwOnIDNotFound);
		bool RemoveIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, bool throwOnIDNotFound);
		bool RemoveUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID, bool throwOnIDNotFound);

		uint32_t GetVertexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;
		MemorySize GetVertexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;
		MemorySize GetVertexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;

		uint32_t GetStagingBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const;
		MemorySize GetStagingBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const;
		MemorySize GetStagingBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const;

		uint32_t GetIndexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const;
		MemorySize GetIndexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const;
		MemorySize GetIndexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const;

		uint32_t GetUniformBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID) const;
		MemorySize GetUniformBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID) const;
		MemorySize GetUniformBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID) const;

		void WriteToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);
		void WriteToStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);
		void WriteToIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);
		void WriteToUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize dataSize);

	private:
		VulkanSimplifiedInternal::DataBufferListsInternal& _internal;
	};
}