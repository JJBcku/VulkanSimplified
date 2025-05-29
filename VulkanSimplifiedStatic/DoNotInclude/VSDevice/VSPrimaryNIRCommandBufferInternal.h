#pragma once

#include "VSCommandBufferBaseInternal.h"

#include "../../Include/VSDevice/VSImageDataListsDef.h"
#include "../../Include/VSDevice/VSRenderPassDataListDef.h"

#include "../../Include/VSSharedData/VSRenderPassClearValueID.h"

#include "../../Include/VSCommon/VSPipelineStageFlagsDef.h"

namespace VulkanSimplified
{
	struct QueueOwnershipTransferData;
}

namespace VulkanSimplifiedInternal
{
	class PrimaryNIRCommandBufferInternal : public CommandBufferBaseInternal
	{
	public:
		PrimaryNIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
		~PrimaryNIRCommandBufferInternal();

		PrimaryNIRCommandBufferInternal(const PrimaryNIRCommandBufferInternal&) noexcept = delete;
		PrimaryNIRCommandBufferInternal(PrimaryNIRCommandBufferInternal&& rhs) noexcept;

		PrimaryNIRCommandBufferInternal& operator=(const PrimaryNIRCommandBufferInternal&) noexcept = delete;
		PrimaryNIRCommandBufferInternal& operator=(PrimaryNIRCommandBufferInternal&& rhs) noexcept = delete;

		void BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, uint32_t startX, uint32_t startY,
			uint32_t width, uint32_t height, const std::vector<std::optional<VulkanSimplified::RenderPassClearValueID>>& clearValues, bool usesSecondaryBuffers);
		void EndRenderPass();

		void TransitionSwapchainImageToTrasferDestination(IDObject<VulkanSimplified::WindowPointer> windowID,
			std::optional<VulkanSimplified::QueueOwnershipTransferData> queueOwnershipTransferData, uint32_t imagesIndex);
		void TransitionSwapchainImageToPresent(IDObject<VulkanSimplified::WindowPointer> windowID,
			std::optional<VulkanSimplified::QueueOwnershipTransferData> queueOwnershipTransferData, uint32_t imagesIndex);

		void BlitToSwapchainImage(IDObject<VulkanSimplified::WindowPointer> windowID, IDObject<AutoCleanupColorRenderTargetImage> imageID, uint32_t startX, uint32_t startY,
			uint32_t width, uint32_t height, uint32_t swapchainImageIndex);
	};
}