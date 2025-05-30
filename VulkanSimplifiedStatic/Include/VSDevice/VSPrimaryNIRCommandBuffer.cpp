#include "VSDeviceIpch.h"
#include "VSPrimaryNIRCommandBuffer.h"

#include <CustomLists/IDObject.h>

#include "../../DoNotInclude/VSDevice/VSPrimaryNIRCommandBufferInternal.h"

#include "VSQueueOwnershipTransferData.h"

namespace VulkanSimplified
{
	PrimaryNIRCommandBuffer::PrimaryNIRCommandBuffer(VulkanSimplifiedInternal::PrimaryNIRCommandBufferInternal& ref) : CommandBufferBase(ref), _internal(ref)
	{
	}

	PrimaryNIRCommandBuffer::~PrimaryNIRCommandBuffer()
	{
	}

	void PrimaryNIRCommandBuffer::BeginRenderPass(IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPassID,
		IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> framebufferID, uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
		const std::vector<std::optional<RenderPassClearValueID>>& clearValues, bool usesSecondaryBuffers)
	{
		_internal.BeginRenderPass(renderPassID, framebufferID, startX, startY, width, height, clearValues, usesSecondaryBuffers);
	}

	void PrimaryNIRCommandBuffer::EndRenderPass()
	{
		_internal.EndRenderPass();
	}

	void PrimaryNIRCommandBuffer::TransitionSwapchainImageToTrasferDestination(IDObject<WindowPointer> windowID, std::optional<QueueOwnershipTransferData> queueOwnershipTransferData,
		uint32_t imagesIndex)
	{
		_internal.TransitionSwapchainImageToTrasferDestination(windowID, queueOwnershipTransferData, imagesIndex);
	}

	void PrimaryNIRCommandBuffer::TransitionSwapchainImageToPresent(IDObject<WindowPointer> windowID, std::optional<QueueOwnershipTransferData> queueOwnershipTransferData,
		uint32_t imagesIndex)
	{
		_internal.TransitionSwapchainImageToPresent(windowID, queueOwnershipTransferData, imagesIndex);
	}

	void PrimaryNIRCommandBuffer::BlitToSwapchainImage(IDObject<WindowPointer> windowID, IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID,
		uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, uint32_t swapchainImageIndex)
	{
		_internal.BlitToSwapchainImage(windowID, imageID, startX, startY, width, height, swapchainImageIndex);
	}
}