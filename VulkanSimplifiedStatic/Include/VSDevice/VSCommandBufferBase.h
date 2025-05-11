#pragma once

#include <CustomLists/IDObjectDef.h>

#include "VSPipelineDataListsDef.h"
#include "VSSynchronizationDataListsDef.h"
#include "VSWindowListDef.h"
#include "VSDataBufferListsDef.h"

#include "VSCommandBufferUsage.h"

#include "../VSCommon/VSPipelineStageFlagsDef.h"

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

		bool AcquireNextImage(uint64_t timeout, std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> semaphoreID,
			std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> fenceID, uint32_t& returnIndex, IDObject<WindowPointer> windowID);

		void TranferDataToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> dstBufferID, const DataBuffersCopyRegionData& copyRegion);
		void TranferDataListToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> srcBufferID,
			IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> dstBufferID, const std::vector<DataBuffersCopyRegionData>& copyRegionsList);

		void CreatePipelineBarrier(PipelineStageFlags srcStages, PipelineStageFlags dstStages, const std::vector<GlobalMemoryBarrierData>& globalMemoryBarrierData,
			const std::vector<DataBuffersMemoryBarrierData>& dataBuffersBarrierData, const std::vector<ImagesMemoryBarrierData>& imageBarrierData);

	private:
		VulkanSimplifiedInternal::CommandBufferBaseInternal& _internal;
	};
}