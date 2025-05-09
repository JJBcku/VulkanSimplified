#pragma once

#include <CustomLists/IDObjectDef.h>

#include "../../Include/VSDevice/VSPipelineDataListsDef.h"
#include "../../Include/VSDevice/VSDataBufferListsDef.h"
#include "../../Include/VSDevice/VSSynchronizationDataListsDef.h"
#include "../../Include/VSDevice/VSWindowListDef.h"

#include "../../Include/VSDevice/VSCommandBufferUsage.h"

#include "../../Include/VSCommon/VSMemorySizeDef.h"

namespace VulkanSimplified
{
	struct DataBuffersCopyRegionData;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
	class WindowListInternal;
	class RenderPassListInternal;
	class PipelineDataListsInternal;
	class ImageDataListsInternal;
	class DataBufferListsInternal;
	class SynchronizationDataListsInternal;

	class SharedRenderPassDataListInternal;

	class CommandBufferBaseInternal
	{
	public:
		CommandBufferBaseInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData, const SharedRenderPassDataListInternal& sharedRenderPassData,
			const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList, const ImageDataListsInternal& imageList,
			DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
		~CommandBufferBaseInternal();

		CommandBufferBaseInternal(const CommandBufferBaseInternal&) noexcept = delete;
		CommandBufferBaseInternal(CommandBufferBaseInternal&& rhs) noexcept;

		CommandBufferBaseInternal& operator=(const CommandBufferBaseInternal&) noexcept = delete;
		CommandBufferBaseInternal& operator=(CommandBufferBaseInternal&& rhs) noexcept = delete;

		VkCommandBuffer GetCommandBuffer() const;

		void BeginRecording(VulkanSimplified::CommandBufferUsage usage);
		void EndRecording();

		void BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

		bool AcquireNextImage(uint64_t timeout, std::optional<IDObject<AutoCleanupSemaphore>> semaphoreID, std::optional<IDObject<AutoCleanupFence>> fenceID,
			uint32_t& returnIndex, IDObject<VulkanSimplified::WindowPointer> windowID);

		void TranferDataToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupVertexBuffer> dstBufferID,
			const VulkanSimplified::DataBuffersCopyRegionData& copyRegion);
		void TranferDataListToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupVertexBuffer> dstBufferID,
			const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList);

	protected:
		const DeviceCoreInternal& _core;

		const RenderPassListInternal& _deviceRenderPassData;
		const SharedRenderPassDataListInternal& _sharedRenderPassData;

		const PipelineDataListsInternal& _devicePipelineData;
		const SynchronizationDataListsInternal& _synchronizationList;

		const ImageDataListsInternal& _imageList;
		DataBufferListsInternal& _dataBufferList;

		WindowListInternal& _windowList;

		VkDevice _device;
		VkCommandBuffer _buffer;

		VkQueue _queue;
	};
}