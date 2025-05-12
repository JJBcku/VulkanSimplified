#include "VSDeviceIpch.h"
#include "VSCommandBufferBase.h"

#include <CustomLists/IDObject.h>

#include "../../DoNotInclude/VSDevice/VSCommandBufferBaseInternal.h"

namespace VulkanSimplified
{
	CommandBufferBase::CommandBufferBase(VulkanSimplifiedInternal::CommandBufferBaseInternal& ref) : _internal(ref)
	{
	}

	CommandBufferBase::~CommandBufferBase()
	{
	}

	void CommandBufferBase::BeginRecording(CommandBufferUsage usage)
	{
		_internal.BeginRecording(usage);
	}

	void CommandBufferBase::EndRecording()
	{
		_internal.EndRecording();
	}

	void CommandBufferBase::BindGraphicsPipeline(IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> pipelineID)
	{
		_internal.BindGraphicsPipeline(pipelineID);
	}

	void CommandBufferBase::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		_internal.Draw(vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void CommandBufferBase::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t firstVertexOffset, uint32_t firstInstance)
	{
		_internal.DrawIndexed(indexCount, instanceCount, firstIndex, firstVertexOffset, firstInstance);
	}

	bool CommandBufferBase::AcquireNextImage(uint64_t timeout, std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> semaphoreID,
		std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> fenceID, uint32_t& returnIndex, IDObject<WindowPointer> windowID)
	{
		return _internal.AcquireNextImage(timeout, semaphoreID, fenceID, returnIndex, windowID);
	}

	void CommandBufferBase::TranferDataToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
		IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> dstBufferID, const DataBuffersCopyRegionData& copyRegion)
	{
		_internal.TranferDataToVertexBuffer(srcBufferID, dstBufferID, copyRegion);
	}

	void CommandBufferBase::TranferDataListToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
		IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> dstBufferID, const std::vector<DataBuffersCopyRegionData>& copyRegionsList)
	{
		_internal.TranferDataListToVertexBuffer(srcBufferID, dstBufferID, copyRegionsList);
	}

	void CommandBufferBase::TranferDataToIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
		IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> dstBufferID, const VulkanSimplified::DataBuffersCopyRegionData& copyRegion)
	{
		_internal.TranferDataToIndexBuffer(srcBufferID, dstBufferID, copyRegion);
	}

	void CommandBufferBase::TranferDataListToIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
		IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> dstBufferID, const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList)
	{
		_internal.TranferDataListToIndexBuffer(srcBufferID, dstBufferID, copyRegionsList);
	}

	void CommandBufferBase::CreatePipelineBarrier(PipelineStageFlags srcStages, PipelineStageFlags dstStages, const std::vector<GlobalMemoryBarrierData>& globalMemoryBarrierData,
		const std::vector<DataBuffersMemoryBarrierData>& dataBuffersBarrierData, const std::vector<ImagesMemoryBarrierData>& imageBarrierData)
	{
		_internal.CreatePipelineBarrier(srcStages, dstStages, globalMemoryBarrierData, dataBuffersBarrierData, imageBarrierData);
	}

	void CommandBufferBase::BindVertexBuffers(uint32_t firstBinding,
		const std::vector<std::pair<IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer>, VulkanSimplified::MemorySize>>& buffersDataList)
	{
		_internal.BindVertexBuffers(firstBinding, buffersDataList);
	}

	void CommandBufferBase::BindIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, MemorySize buffersOffset, IndexType indexType)
	{
		_internal.BindIndexBuffer(bufferID, buffersOffset, indexType);
	}

}