#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSDevice/VSCommandBufferGenericIDDef.h"
#include "../../Include/VSDevice/VSCommandPoolQFGroupListDef.h"
#include "../../Include/VSDevice/VSNIRCommandPoolDef.h"
#include "../../Include/VSDevice/VSIRCommandPoolDef.h"

namespace VulkanSimplified
{
	struct CommandPoolQFGroupListsInitialCapacities;

	struct CommandBufferSubmissionData;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
	class RenderPassListInternal;
	class PipelineDataListsInternal;
	class SynchronizationDataListsInternal;
	class ImageDataListsInternal;
	class WindowListInternal;

	class SharedRenderPassDataListInternal;

	class AutoCleanupFence;

	class CommandPoolQFGroupListInternal
	{
	public:
		CommandPoolQFGroupListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, const ImageDataListsInternal& imageList, WindowListInternal& windowList,
			size_t queueFamily, const VulkanSimplified::CommandPoolQFGroupListsInitialCapacities& initialCapacities);
		~CommandPoolQFGroupListInternal();

		CommandPoolQFGroupListInternal(const CommandPoolQFGroupListInternal&) noexcept = delete;
		CommandPoolQFGroupListInternal(CommandPoolQFGroupListInternal&&) noexcept = delete;

		CommandPoolQFGroupListInternal& operator=(const CommandPoolQFGroupListInternal&) noexcept = delete;
		CommandPoolQFGroupListInternal& operator=(CommandPoolQFGroupListInternal&&) noexcept = delete;

		IDObject<VulkanSimplified::NIRPoolPointer> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
			size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving);
		IDObject<VulkanSimplified::IRPoolPointer> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
			size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving);

		NIRCommandPoolInternal& GetCommandPoolWithoutIndividualReset(IDObject<VulkanSimplified::NIRPoolPointer> poolID);
		IRCommandPoolInternal& GetCommandPoolWithIndividualReset(IDObject<VulkanSimplified::IRPoolPointer> poolID);

		const NIRCommandPoolInternal& GetCommandPoolWithoutIndividualReset(IDObject<VulkanSimplified::NIRPoolPointer> poolID) const;
		const IRCommandPoolInternal& GetCommandPoolWithIndividualReset(IDObject<VulkanSimplified::IRPoolPointer> poolID) const;

		void SubmitBuffers(size_t queueID, const std::vector<VulkanSimplified::CommandBufferSubmissionData>& submissionData, std::optional<IDObject<AutoCleanupFence>> fenceID);

	private:
		const DeviceCoreInternal& _deviceCore;

		const RenderPassListInternal& _deviceRenderPassData;
		const SharedRenderPassDataListInternal& _sharedRenderPassData;

		const PipelineDataListsInternal& _devicePipelineData;
		const SynchronizationDataListsInternal& _synchronizationList;

		const ImageDataListsInternal& _imageList;

		WindowListInternal& _windowList;

		VkDevice _device;

		size_t _queueFamily;

		UnsortedIDVector<VulkanSimplified::NIRPoolPointer> _noIndividualResetCommandPoolList;
		UnsortedIDVector<VulkanSimplified::IRPoolPointer> _individualResetCommandPoolList;

		VkCommandBuffer GetCommandBuffer(VulkanSimplified::CommandBufferGenericID bufferID) const;

		VkCommandBuffer GetCommandBuffer(IDObject<VulkanSimplified::NIRPoolPointer> commandPoolID,
			IDObject<VulkanSimplified::PrimaryNIRPointer> commandBufferID) const;
		VkCommandBuffer GetCommandBuffer(IDObject<VulkanSimplified::NIRPoolPointer> commandPoolID,
			IDObject<VulkanSimplified::SecondaryNIRPointer> commandBufferID) const;
		VkCommandBuffer GetCommandBuffer(IDObject<VulkanSimplified::IRPoolPointer> commandPoolID,
			IDObject<VulkanSimplified::PrimaryIRPointer> commandBufferID) const;
		VkCommandBuffer GetCommandBuffer(IDObject<VulkanSimplified::IRPoolPointer> commandPoolID,
			IDObject<VulkanSimplified::SecondaryIRPointer> commandBufferID) const;
	};
}