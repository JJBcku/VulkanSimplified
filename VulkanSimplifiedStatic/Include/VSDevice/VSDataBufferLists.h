#pragma once

#include "VSDataBufferListsDef.h"

#include "../VSCommon/VSMemorySizeDef.h"
#include "../VSCommon/VSMemoryAllocationFullID.h"

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

		IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingImage, size_t addOnReserving = 0);

		void BindVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving = 0);

		uint32_t GetVertexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;
		VulkanSimplified::MemorySize GetVertexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const;

	private:
		VulkanSimplifiedInternal::DataBufferListsInternal& _internal;
	};
}