#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../../Include/VSDevice/VSCommandBufferGenericIDDef.h"
#include "../../../Include/VSDevice/VSCommandPoolQFGroupListDef.h"
#include "../../../Include/VSDevice/VSNIRCommandPoolDef.h"
#include "../../../Include/VSDevice/VSIRCommandPoolDef.h"

#include <optional>
#include <vector>

typedef struct VkDevice_T* VkDevice;
typedef struct VkCommandBuffer_T* VkCommandBuffer;

namespace VulkanSimplified
{
	struct CommandPoolQFGroupListsInitialCapacities;

	struct CommandBufferSubmissionData;
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

	class SharedRenderPassDataListsInternal;

	class AutoCleanupFence;

	class CommandPoolQFGroupListInternal
	{
	public:
		CommandPoolQFGroupListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListsInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, size_t queueFamily,
			const CommandPoolQFGroupListsInitialCapacities& initialCapacities);
		~CommandPoolQFGroupListInternal();

		CommandPoolQFGroupListInternal(const CommandPoolQFGroupListInternal&) noexcept = delete;
		CommandPoolQFGroupListInternal(CommandPoolQFGroupListInternal&&) noexcept = delete;

		CommandPoolQFGroupListInternal& operator=(const CommandPoolQFGroupListInternal&) noexcept = delete;
		CommandPoolQFGroupListInternal& operator=(CommandPoolQFGroupListInternal&&) noexcept = delete;

		IDObject<NIRPoolPointer> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
			size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving);
		IDObject<IRPoolPointer> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
			size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving);

		NIRCommandPoolInternal& GetCommandPoolWithoutIndividualReset(IDObject<NIRPoolPointer> poolID);
		IRCommandPoolInternal& GetCommandPoolWithIndividualReset(IDObject<IRPoolPointer> poolID);

		const NIRCommandPoolInternal& GetCommandPoolWithoutIndividualReset(IDObject<NIRPoolPointer> poolID) const;
		const IRCommandPoolInternal& GetCommandPoolWithIndividualReset(IDObject<IRPoolPointer> poolID) const;

		void SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmissionData>& submissionData, std::optional<IDObject<AutoCleanupFence>> fenceID);

	private:
		const DeviceCoreInternal& _deviceCore;

		const RenderPassListInternal& _deviceRenderPassData;
		const SharedRenderPassDataListsInternal& _sharedRenderPassData;

		const PipelineDataListsInternal& _devicePipelineData;
		const SynchronizationDataListsInternal& _synchronizationList;

		ImageDataListsInternal& _imageList;
		DataBufferListsInternal& _dataBufferList;

		WindowListInternal& _windowList;
		DescriptorDataListsInternal& _descriptorDataList;

		VkDevice _device;

		size_t _queueFamily;

		UnsortedIDVector<NIRPoolPointer> _noIndividualResetCommandPoolList;
		UnsortedIDVector<IRPoolPointer> _individualResetCommandPoolList;

		VkCommandBuffer GetCommandBuffer(CommandBufferGenericID bufferID) const;

		VkCommandBuffer GetCommandBuffer(IDObject<NIRPoolPointer> commandPoolID,
			IDObject<PrimaryNIRPointer> commandBufferID) const;
		VkCommandBuffer GetCommandBuffer(IDObject<NIRPoolPointer> commandPoolID,
			IDObject<SecondaryNIRPointer> commandBufferID) const;
		VkCommandBuffer GetCommandBuffer(IDObject<IRPoolPointer> commandPoolID,
			IDObject<PrimaryIRPointer> commandBufferID) const;
		VkCommandBuffer GetCommandBuffer(IDObject<IRPoolPointer> commandPoolID,
			IDObject<SecondaryIRPointer> commandBufferID) const;
	};
}