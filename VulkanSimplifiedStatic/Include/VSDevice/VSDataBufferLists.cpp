#include "VSDeviceIpch.h"
#include "VSDataBufferLists.h"

#include "../../DoNotInclude/VSDevice/VSDataBufferListsInternal.h"

namespace VulkanSimplified
{
	DataBufferLists::DataBufferLists(VulkanSimplifiedInternal::DataBufferListsInternal& ref) : _internal(ref)
	{
	}

	DataBufferLists::~DataBufferLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> DataBufferLists::AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddVertexBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> DataBufferLists::AddStagingBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddStagingBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	void DataBufferLists::BindVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindVertexBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindStagingBuffer(bufferID, allocationID, addOnReserving);
	}

	uint32_t DataBufferLists::GetVertexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersMemoryTypeMask(bufferID);
	}

	VulkanSimplified::MemorySize VulkanSimplified::DataBufferLists::GetVertexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersSize(bufferID);
	}

	VulkanSimplified::MemorySize DataBufferLists::GetVertexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetStagingBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersMemoryTypeMask(bufferID);
	}

	VulkanSimplified::MemorySize DataBufferLists::GetStagingBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersSize(bufferID);
	}

	VulkanSimplified::MemorySize DataBufferLists::GetStagingBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersRequiredAligment(bufferID);
	}

	void DataBufferLists::WriteToStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData, MemorySize dataSize)
	{
		_internal.WriteToStagingBuffer(bufferID, writeOffset, writeData, dataSize);
	}

}