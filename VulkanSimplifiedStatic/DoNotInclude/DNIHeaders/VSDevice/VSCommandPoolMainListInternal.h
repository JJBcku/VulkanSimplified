#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../../Include/VSDevice/VSCommandPoolMainListDef.h"

#include <stdint.h>

typedef struct VkDevice_T* VkDevice;

namespace VulkanSimplified
{
	struct CommandPoolMainListInitialCapacity;
	struct CommandPoolQFGroupListsInitialCapacities;
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

	class CommandPoolMainListInternal
	{
	public:
		CommandPoolMainListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, const CommandPoolMainListInitialCapacity& initialCapacity);
		~CommandPoolMainListInternal();

		CommandPoolMainListInternal(const CommandPoolMainListInternal&) noexcept = delete;
		CommandPoolMainListInternal(CommandPoolMainListInternal&&) noexcept = delete;

		CommandPoolMainListInternal& operator=(const CommandPoolMainListInternal&) noexcept = delete;
		CommandPoolMainListInternal& operator=(CommandPoolMainListInternal&&) noexcept = delete;

		IDObject<CommandPoolQFGroupPointer> AddQueueFamiliesPoolGroup(uint32_t queueFamily,
			const CommandPoolQFGroupListsInitialCapacities& initialCapacities, size_t addOnReserving);

		CommandPoolQFGroupListInternal& GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID);

		const CommandPoolQFGroupListInternal& GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID) const;

	private:
		const DeviceCoreInternal& _deviceCore;

		const RenderPassListInternal& _deviceRenderPassData;
		const SharedRenderPassDataListInternal& _sharedRenderPassData;

		const PipelineDataListsInternal& _devicePipelineData;
		const SynchronizationDataListsInternal& _synchronizationList;

		ImageDataListsInternal& _imageList;
		DataBufferListsInternal& _dataBufferList;

		WindowListInternal& _windowList;
		DescriptorDataListsInternal& _descriptorDataList;

		VkDevice _device;

		UnsortedIDVector<CommandPoolQFGroupPointer> _qfGroupList;
	};
}