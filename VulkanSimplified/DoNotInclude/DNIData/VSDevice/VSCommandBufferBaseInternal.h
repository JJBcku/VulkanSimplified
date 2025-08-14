#pragma once

#include <CustomLists/IDObjectDef.h>

#include "../../../Include/VSDevice/VSPipelineDataListsDef.h"
#include "../../../Include/VSDevice/VSRenderPassDataListDef.h"
#include "../../../Include/VSDevice/VSDataBufferListsDef.h"
#include "../../../Include/VSDevice/VSDescriptorDataListsDef.h"
#include "../../../Include/VSDevice/VSImageDataListsDef.h"
#include "../../../Include/VSDevice/VSSynchronizationDataListsDef.h"
#include "../../../Include/VSDevice/VSWindowListDef.h"
#include "../../../Include/VSDevice/VSIndexTypeDef.h"

#include "../../../Include/VSDevice/VSCommandBufferUsage.h"

#include "../../../Include/VSCommon/VSMemorySizeDef.h"
#include "../../../Include/VSCommon/VSPipelineStageFlagsDef.h"

#include <optional>
#include <vector>
#include <utility>
#include <stdint.h>

typedef struct VkDevice_T* VkDevice;
typedef struct VkCommandBuffer_T* VkCommandBuffer;
typedef struct VkQueue_T* VkQueue;

namespace VulkanSimplified
{
	struct DataBuffersCopyRegionData;

	struct GlobalMemoryBarrierData;
	struct DataBuffersMemoryBarrierData;
	struct ImagesMemoryBarrierData;

	union DescriptorPoolGenericID;
}

namespace VulkanSimplified
{
	class DeviceCoreInternal;
	class WindowListInternal;
	class RenderPassListInternal;
	class PipelineDataListsInternal;
	class ImageDataListsInternal;
	class DataBufferListsInternal;
	class SynchronizationDataListsInternal;
	class DescriptorDataListsInternal;

	class SharedRenderPassDataListInternal;

	class CommandBufferBaseInternal
	{
	public:
		CommandBufferBaseInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData, const SharedRenderPassDataListInternal& sharedRenderPassData,
			const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList,
			DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device, VkCommandBuffer buffer,
			VkQueue queue);
		~CommandBufferBaseInternal();

		CommandBufferBaseInternal(const CommandBufferBaseInternal&) noexcept = delete;
		CommandBufferBaseInternal(CommandBufferBaseInternal&& rhs) noexcept;

		CommandBufferBaseInternal& operator=(const CommandBufferBaseInternal&) noexcept = delete;
		CommandBufferBaseInternal& operator=(CommandBufferBaseInternal&& rhs) noexcept = delete;

		VkCommandBuffer GetCommandBuffer() const;

		void EndRecording();

		void BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t firstVertexOffset, uint32_t firstInstance);

		void TransferDataToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupVertexBuffer> dstBufferID,
			const DataBuffersCopyRegionData& copyRegion);
		void TransferDataListToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupVertexBuffer> dstBufferID,
			const std::vector<DataBuffersCopyRegionData>& copyRegionsList);

		void TransferDataToIndexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupIndexBuffer> dstBufferID,
			const DataBuffersCopyRegionData& copyRegion);
		void TransferDataListToIndexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupIndexBuffer> dstBufferID,
			const std::vector<DataBuffersCopyRegionData>& copyRegionsList);

		void TransferDataToUniformBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupUniformBuffer> dstBufferID,
			const DataBuffersCopyRegionData& copyRegion);
		void TransferDataListToUniformBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupUniformBuffer> dstBufferID,
			const std::vector<DataBuffersCopyRegionData>& copyRegionsList);

		void TransferDataTo2dTextureSimple(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanup2DTexture> dstTextureID, uint32_t mipLevel);

		void TransferDataTo2dArrayTextureSingleLayer(IDObject<AutoCleanupStagingBuffer> srcBufferID, size_t bufferOffset, size_t dataSize,
			IDObject<AutoCleanup2DArrayTexture> dstTextureID, uint32_t startWidth, uint32_t startHeight, uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t layer);

		void BlitDataBetween2DTexturesSimple(IDObject<AutoCleanup2DTexture> srcTexureID, uint32_t srcMipLevel, IDObject<AutoCleanup2DTexture> dstTextureID, uint32_t dstMipLevel);

		void CreatePipelineBarrier(PipelineStageFlags srcStages, PipelineStageFlags dstStages,
			const std::vector<GlobalMemoryBarrierData>& globalMemoryBarrierData,
			const std::vector<DataBuffersMemoryBarrierData>& dataBuffersBarrierData, const std::vector<ImagesMemoryBarrierData>& imageBarrierData);

		void BindVertexBuffers(uint32_t firstBinding, const std::vector<std::pair<IDObject<AutoCleanupVertexBuffer>, MemorySize>>& buffersDataList);
		void BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemorySize buffersOffset, IndexType indexType);

		void BindDescriptorSetsToGraphicsPipeline(IDObject<AutoCleanupPipelineLayout> pipelineLayoutID, uint32_t firstSet, DescriptorPoolGenericID descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDList, const std::vector<uint32_t>& dynamicOffsetList);

	protected:
		const DeviceCoreInternal& _core;

		const RenderPassListInternal& _deviceRenderPassData;
		const SharedRenderPassDataListInternal& _sharedRenderPassData;

		const PipelineDataListsInternal& _devicePipelineData;
		const SynchronizationDataListsInternal& _synchronizationList;

		ImageDataListsInternal& _imageList;
		DataBufferListsInternal& _dataBufferList;

		WindowListInternal& _windowList;
		DescriptorDataListsInternal& _descriptorDataList;

		VkDevice _device;
		VkCommandBuffer _buffer;

		VkQueue _queue;
	};
}