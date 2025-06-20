#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSCommandBufferBase.h"

#include <CustomLists/IDObject.h>

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSCommandBufferBaseInternal.h"

#include "../../../Include/VSDevice/VSDescriptorPoolGenericID.h"

namespace VulkanSimplified
{
	CommandBufferBase::CommandBufferBase(CommandBufferBaseInternal& ref) : _internal(ref)
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

	void CommandBufferBase::BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID)
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

	bool CommandBufferBase::AcquireNextImage(uint64_t timeout, std::optional<IDObject<AutoCleanupSemaphore>> semaphoreID,
		std::optional<IDObject<AutoCleanupFence>> fenceID, uint32_t& returnIndex, IDObject<WindowPointer> windowID)
	{
		return _internal.AcquireNextImage(timeout, semaphoreID, fenceID, returnIndex, windowID);
	}

	void CommandBufferBase::TransferDataToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanupVertexBuffer> dstBufferID, const DataBuffersCopyRegionData& copyRegion)
	{
		_internal.TransferDataToVertexBuffer(srcBufferID, dstBufferID, copyRegion);
	}

	void CommandBufferBase::TransferDataListToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanupVertexBuffer> dstBufferID, const std::vector<DataBuffersCopyRegionData>& copyRegionsList)
	{
		_internal.TransferDataListToVertexBuffer(srcBufferID, dstBufferID, copyRegionsList);
	}

	void CommandBufferBase::TransferDataToIndexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanupIndexBuffer> dstBufferID, const DataBuffersCopyRegionData& copyRegion)
	{
		_internal.TransferDataToIndexBuffer(srcBufferID, dstBufferID, copyRegion);
	}

	void CommandBufferBase::TransferDataListToIndexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanupIndexBuffer> dstBufferID, const std::vector<DataBuffersCopyRegionData>& copyRegionsList)
	{
		_internal.TransferDataListToIndexBuffer(srcBufferID, dstBufferID, copyRegionsList);
	}

	void CommandBufferBase::TransferDataToUniformBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanupUniformBuffer> dstBufferID, const DataBuffersCopyRegionData& copyRegion)
	{
		_internal.TransferDataToUniformBuffer(srcBufferID, dstBufferID, copyRegion);
	}

	void CommandBufferBase::TransferDataListToUniformBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanupUniformBuffer> dstBufferID, const std::vector<DataBuffersCopyRegionData>& copyRegionsList)
	{
		_internal.TransferDataListToUniformBuffer(srcBufferID, dstBufferID, copyRegionsList);
	}

	void CommandBufferBase::TransferDataTo2dTextureSimple(IDObject<AutoCleanupStagingBuffer> srcBufferID,
		IDObject<AutoCleanup2DTexture> dstTextureID, uint32_t mipLevel)
	{
		_internal.TransferDataTo2dTextureSimple(srcBufferID, dstTextureID, mipLevel);
	}

	void CommandBufferBase::BlitDataBetween2DTexturesSimple(IDObject<AutoCleanup2DTexture> srcTexureID, uint32_t srcMipLevel,
		IDObject<AutoCleanup2DTexture> dstTextureID, uint32_t dstMipLevel)
	{
		_internal.BlitDataBetween2DTexturesSimple(srcTexureID, srcMipLevel, dstTextureID, dstMipLevel);
	}

	void CommandBufferBase::CreatePipelineBarrier(PipelineStageFlags srcStages, PipelineStageFlags dstStages, const std::vector<GlobalMemoryBarrierData>& globalMemoryBarrierData,
		const std::vector<DataBuffersMemoryBarrierData>& dataBuffersBarrierData, const std::vector<ImagesMemoryBarrierData>& imageBarrierData)
	{
		_internal.CreatePipelineBarrier(srcStages, dstStages, globalMemoryBarrierData, dataBuffersBarrierData, imageBarrierData);
	}

	void CommandBufferBase::BindVertexBuffers(uint32_t firstBinding,
		const std::vector<std::pair<IDObject<AutoCleanupVertexBuffer>, MemorySize>>& buffersDataList)
	{
		_internal.BindVertexBuffers(firstBinding, buffersDataList);
	}

	void CommandBufferBase::BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemorySize buffersOffset, IndexType indexType)
	{
		_internal.BindIndexBuffer(bufferID, buffersOffset, indexType);
	}

	void CommandBufferBase::BindDescriptorSetsToGraphicsPipeline(IDObject<AutoCleanupPipelineLayout> pipelineLayoutID, uint32_t firstSet,
		DescriptorPoolGenericID descriptorPoolID, const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDList,
		const std::vector<uint32_t>& dynamicOffsetList)
	{
		_internal.BindDescriptorSetsToGraphicsPipeline(pipelineLayoutID, firstSet, descriptorPoolID, descriptorSetIDList, dynamicOffsetList);
	}

}