#pragma once

#include <CustomLists/IDObjectDef.h>

#include "VSPipelineDataListsDef.h"
#include "VSSynchronizationDataListsDef.h"
#include "VSWindowListDef.h"
#include "VSDataBufferListsDef.h"
#include "VSImageDataListsDef.h"
#include "VSIndexTypeDef.h"
#include "VSDescriptorDataListDef.h"

#include "VSCommandBufferUsage.h"

#include "../VSCommon/VSPipelineStageFlagsDef.h"
#include "../VSCommon/VSMemorySizeDef.h"

namespace VulkanSimplifiedInternal
{
	class CommandBufferBaseInternal;
}

namespace VulkanSimplified
{
	struct DataBuffersCopyRegionData;

	struct GlobalMemoryBarrierData;
	struct DataBuffersMemoryBarrierData;
	struct ImagesMemoryBarrierData;

	union DescriptorPoolGenericID;

	class CommandBufferBase
	{
	public:
		CommandBufferBase(VulkanSimplifiedInternal::CommandBufferBaseInternal& ref);
		~CommandBufferBase();

		CommandBufferBase& operator=(const CommandBufferBase& rhs) noexcept = delete;

		void BeginRecording(CommandBufferUsage usage);
		void EndRecording();

		void BindGraphicsPipeline(IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> pipelineID);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t firstVertexOffset, uint32_t firstInstance);

		bool AcquireNextImage(uint64_t timeout, std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> semaphoreID,
			std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> fenceID, uint32_t& returnIndex, IDObject<WindowPointer> windowID);

		void TransferDataToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID, IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> dstBufferID,
			const DataBuffersCopyRegionData& copyRegion);
		void TransferDataListToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> dstBufferID, const std::vector<DataBuffersCopyRegionData>& copyRegionsList);

		void TransferDataToIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID, IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> dstBufferID,
			const VulkanSimplified::DataBuffersCopyRegionData& copyRegion);
		void TransferDataListToIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> dstBufferID, const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList);

		void TransferDataToUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> dstBufferID, const VulkanSimplified::DataBuffersCopyRegionData& copyRegion);
		void TransferDataListToUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> dstBufferID, const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList);

		void TransferDataTo2dTextureSimple(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> dstTextureID, uint32_t mipLevel);

		void CreatePipelineBarrier(PipelineStageFlags srcStages, PipelineStageFlags dstStages, const std::vector<GlobalMemoryBarrierData>& globalMemoryBarrierData,
			const std::vector<DataBuffersMemoryBarrierData>& dataBuffersBarrierData, const std::vector<ImagesMemoryBarrierData>& imageBarrierData);

		void BindVertexBuffers(uint32_t firstBinding,
			const std::vector<std::pair<IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer>, VulkanSimplified::MemorySize>>& buffersDataList);
		void BindIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, MemorySize buffersOffset, IndexType indexType);

		void BindDescriptorSetsToGraphicsPipeline(IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> pipelineLayoutID, uint32_t firstSet,
			VulkanSimplified::DescriptorPoolGenericID descriptorPoolID, const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet>>& descriptorSetIDList,
			const std::vector<uint32_t>& dynamicOffsetList);

	private:
		VulkanSimplifiedInternal::CommandBufferBaseInternal& _internal;
	};
}