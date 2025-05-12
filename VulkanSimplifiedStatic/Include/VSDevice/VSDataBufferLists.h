#pragma once

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
		IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> AddIndexBuffer(size_t indicesCount, VulkanSimplified::IndexType indexType,
			const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving = 0);

		void BindVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving = 0);
		void BindStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving = 0);
		void BindIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving = 0);

		uint32_t GetVertexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;

		uint32_t GetStagingBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetStagingBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetStagingBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const;

		uint32_t GetIndexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetIndexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetIndexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const;

		void WriteToStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData, MemorySize dataSize);

	private:
		VulkanSimplifiedInternal::DataBufferListsInternal& _internal;
	};
}