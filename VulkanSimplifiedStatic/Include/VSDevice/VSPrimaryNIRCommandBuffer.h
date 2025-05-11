#pragma once

#include <CustomLists/IDObjectDef.h>

#include "VSCommandBufferBase.h"
#include "VSWindowListDef.h"
#include "VSRenderPassDataListDef.h"
#include "VSImageDataListsDef.h"

#include "../VSSharedData/VSRenderPassClearValueIDDef.h"

namespace VulkanSimplifiedInternal
{
	class PrimaryNIRCommandBufferInternal;
}

namespace VulkanSimplified
{
	struct QueueOwnershipTransferData;

	class PrimaryNIRCommandBuffer : public CommandBufferBase
	{
	public:
		PrimaryNIRCommandBuffer(VulkanSimplifiedInternal::PrimaryNIRCommandBufferInternal& ref);
		~PrimaryNIRCommandBuffer();

		PrimaryNIRCommandBuffer& operator=(const PrimaryNIRCommandBuffer&) noexcept = delete;

		void BeginRenderPass(IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPassID, IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> framebufferID,
			uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, const std::vector<std::optional<RenderPassClearValueID>>& clearValues, bool usesSecondaryBuffers = false);
		void EndRenderPass();

		void TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<QueueOwnershipTransferData> queueOwnershipTransferData, uint32_t imagesIndex);
		void TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<QueueOwnershipTransferData> queueOwnershipTransferData, uint32_t imagesIndex);

		void BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, uint32_t startX, uint32_t startY,
			uint32_t width, uint32_t height, uint32_t swapchainImageIndex);

	private:
		VulkanSimplifiedInternal::PrimaryNIRCommandBufferInternal& _internal;
	};
}