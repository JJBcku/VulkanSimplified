#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSDevice/VSCommandPoolMainListDef.h"

namespace VulkanSimplified
{
	struct CommandPoolMainListInitialCapacity;
	struct CommandPoolQFGroupListsInitialCapacities;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
	class RenderPassListInternal;
	class PipelineDataListsInternal;
	class SynchronizationDataListsInternal;
	class ImageDataListsInternal;
	class DataBufferListsInternal;
	class WindowListInternal;

	class SharedRenderPassDataListInternal;

	class CommandPoolMainListInternal
	{
	public:
		CommandPoolMainListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, const ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList,  const VulkanSimplified::CommandPoolMainListInitialCapacity& initialCapacity);
		~CommandPoolMainListInternal();

		CommandPoolMainListInternal(const CommandPoolMainListInternal&) noexcept = delete;
		CommandPoolMainListInternal(CommandPoolMainListInternal&&) noexcept = delete;

		CommandPoolMainListInternal& operator=(const CommandPoolMainListInternal&) noexcept = delete;
		CommandPoolMainListInternal& operator=(CommandPoolMainListInternal&&) noexcept = delete;

		IDObject<VulkanSimplified::CommandPoolQFGroupPointer> AddQueueFamiliesPoolGroup(uint32_t queueFamily,
			const VulkanSimplified::CommandPoolQFGroupListsInitialCapacities& initialCapacities, size_t addOnReserving);

		CommandPoolQFGroupListInternal& GetQueueFamiliesPoolGroup(IDObject<VulkanSimplified::CommandPoolQFGroupPointer> qfGroupID);

		const CommandPoolQFGroupListInternal& GetQueueFamiliesPoolGroup(IDObject<VulkanSimplified::CommandPoolQFGroupPointer> qfGroupID) const;

	private:
		const DeviceCoreInternal& _deviceCore;

		const RenderPassListInternal& _deviceRenderPassData;
		const SharedRenderPassDataListInternal& _sharedRenderPassData;

		const PipelineDataListsInternal& _devicePipelineData;
		const SynchronizationDataListsInternal& _synchronizationList;

		const ImageDataListsInternal& _imageList;
		DataBufferListsInternal& _dataBufferList;

		WindowListInternal& _windowList;

		VkDevice _device;

		UnsortedIDVector<VulkanSimplified::CommandPoolQFGroupPointer> _qfGroupList;
	};
}