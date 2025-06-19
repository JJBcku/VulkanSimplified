#pragma once

#include "../../Include/VSDevice/VSSynchronizationDataListsDef.h"
#include "../../Include/VSDevice/VSWindowListDef.h"
#include "../../Include/VSDevice/VSNIRCommandPoolDef.h"

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

	class PrimaryNIRCommandBufferInternal;
	class SecondaryNIRCommandBufferInternal;

	class NIRCommandPoolInternal
	{
	public:
		NIRCommandPoolInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData, const SharedRenderPassDataListInternal& sharedRenderPassData,
			const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList,
			DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device, VkCommandPool commandPool, 
			VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity);
		~NIRCommandPoolInternal();

		NIRCommandPoolInternal(const NIRCommandPoolInternal&) noexcept = delete;
		NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept = delete;

		NIRCommandPoolInternal& operator=(const NIRCommandPoolInternal&) noexcept = delete;
		NIRCommandPoolInternal& operator=(NIRCommandPoolInternal&& rhs) noexcept = delete;

		std::vector<IDObject<VulkanSimplified::PrimaryNIRPointer>> AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving);
		std::vector<IDObject<VulkanSimplified::SecondaryNIRPointer>> AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving);

		PrimaryNIRCommandBufferInternal& GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryNIRPointer> bufferID);
		SecondaryNIRCommandBufferInternal& GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryNIRPointer> bufferID);

		const PrimaryNIRCommandBufferInternal& GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryNIRPointer> bufferID) const;
		const SecondaryNIRCommandBufferInternal& GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryNIRPointer> bufferID) const;

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

		UnsortedIDVector<std::unique_ptr<PrimaryNIRCommandBufferInternal>> _primaryBufferList;
		UnsortedIDVector<std::unique_ptr<SecondaryNIRCommandBufferInternal>> _secondaryBufferList;
	};
}