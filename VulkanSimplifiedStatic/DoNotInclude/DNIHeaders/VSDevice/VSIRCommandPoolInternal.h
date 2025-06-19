#pragma once

#include "../../../Include/VSDevice/VSIRCommandPoolDef.h"
#include "../../../Include/VSDevice/VSWindowListDef.h"

#include <CustomLists/UnsortedIDVector.h>
#include <memory>
#include <vector>

typedef struct VkDevice_T* VkDevice;
typedef struct VkCommandPool_T* VkCommandPool;
typedef struct VkQueue_T* VkQueue;

namespace VulkanSimplifiedInternal
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

	class AutoCleanupSemaphore;

	class IRCommandPoolInternal
	{
	public:
		IRCommandPoolInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData, const SharedRenderPassDataListInternal& sharedRenderPassData,
			const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList,
			DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device, VkCommandPool commandPool,
			VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
		~IRCommandPoolInternal();

		IRCommandPoolInternal(const IRCommandPoolInternal&) noexcept = delete;
		IRCommandPoolInternal(IRCommandPoolInternal&& rhs) noexcept = delete;

		IRCommandPoolInternal& operator=(const IRCommandPoolInternal&) noexcept = delete;
		IRCommandPoolInternal& operator=(IRCommandPoolInternal&& rhs) noexcept = delete;

		std::vector<IDObject<VulkanSimplified::PrimaryIRPointer>> AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving);
		std::vector<IDObject<VulkanSimplified::SecondaryIRPointer>> AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving);

		PrimaryIRCommandBufferInternal& GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryIRPointer> bufferID);
		SecondaryIRCommandBufferInternal& GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryIRPointer> bufferID);

		const PrimaryIRCommandBufferInternal& GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryIRPointer> bufferID) const;
		const SecondaryIRCommandBufferInternal& GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryIRPointer> bufferID) const;

		void ResetCommandPool(bool freeResources);

		bool PresentSwapchainToQueue(IDObject<VulkanSimplified::WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs, uint32_t imageIndex);

	private:
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
		VkCommandPool _commandPool;

		VkQueue _queue;

		UnsortedIDVector<std::unique_ptr<PrimaryIRCommandBufferInternal>> _primaryBufferList;
		UnsortedIDVector<std::unique_ptr<SecondaryIRCommandBufferInternal>> _secondaryBufferList;
	};
}