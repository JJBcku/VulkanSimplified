#include "VSDeviceNIpch.h"
#include "VSPrimaryNIRCommandBufferInternal.h"

#include <CustomLists/IDObject.h>

#include "VSDeviceCoreInternal.h"
#include "VSWindowListInternal.h"
#include "VSWindowInternal.h"

#include "VSRenderPassDataListInternal.h"
#include "VSImageDataListsInternal.h"

#include "../../Include/VSSharedData/VSRenderPassClearValueID.h"

#include "../VSSharedData/VSSharedRenderPassDataInternal.h"

#include "../../Include/VSDevice/VSQueueOwnershipTransferData.h"

namespace VulkanSimplifiedInternal
{
	PrimaryNIRCommandBufferInternal::PrimaryNIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList,
		VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
		CommandBufferBaseInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, dataBufferList, windowList,
			descriptorDataList, device, buffer, queue)
	{
	}

	PrimaryNIRCommandBufferInternal::~PrimaryNIRCommandBufferInternal()
	{
	}

	PrimaryNIRCommandBufferInternal::PrimaryNIRCommandBufferInternal(PrimaryNIRCommandBufferInternal&& rhs) noexcept : CommandBufferBaseInternal(std::move(rhs))
	{
	}

	void PrimaryNIRCommandBufferInternal::BeginRenderPass(IDObject<AutoCleanupRenderPass> renderPassID, IDObject<AutoCleanupFramebuffer> framebufferID, uint32_t startX, uint32_t startY,
		uint32_t width, uint32_t height, const std::vector<std::optional<VulkanSimplified::RenderPassClearValueID>>& clearValues, bool usesSecondaryBuffers)
	{
		VkRenderPassBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		beginInfo.renderPass = _deviceRenderPassData.GetRenderPass(renderPassID);
		beginInfo.framebuffer = _imageList.GetFramebuffer(framebufferID);

		beginInfo.renderArea.offset = { static_cast<std::int32_t>(startX), static_cast<std::int32_t>(startY) };
		beginInfo.renderArea.extent = { width, height };

		size_t maxSize = clearValues.size() << 1;
		if (maxSize <= clearValues.size())
			throw std::runtime_error("PrimaryNIRCommandBufferInternal::BeginRenderPass Error: Max size overflowed!");

		std::vector<VkClearValue> clearValuesList;
		clearValuesList.reserve(maxSize);

		for (auto& clearValue : clearValues)
		{
			if (clearValue.has_value())
			{
				auto value = _sharedRenderPassData.GetClearValue(clearValue.value());

				clearValuesList.push_back(value.first);
				if (value.second.has_value())
					clearValuesList.push_back(value.second.value());
			}
			else
			{
				clearValuesList.push_back(VkClearValue());
			}
		}

		beginInfo.clearValueCount = static_cast<std::uint32_t>(clearValuesList.size());
		beginInfo.pClearValues = clearValuesList.data();

		VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE;

		if (usesSecondaryBuffers)
			contents = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;

		vkCmdBeginRenderPass(_buffer, &beginInfo, contents);
	}

	void PrimaryNIRCommandBufferInternal::EndRenderPass()
	{
		vkCmdEndRenderPass(_buffer);
	}

	void PrimaryNIRCommandBufferInternal::TransitionSwapchainImageToTrasferDestination(IDObject<VulkanSimplified::WindowPointer> windowID,
		std::optional<VulkanSimplified::QueueOwnershipTransferData> queueOwnershipTransferData, uint32_t imagesIndex)
	{
		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

		if (queueOwnershipTransferData.has_value())
		{
			barrier.srcQueueFamilyIndex = _core.GetQueuesFamily(queueOwnershipTransferData.value().srcQueueIndex);
			barrier.dstQueueFamilyIndex = _core.GetQueuesFamily(queueOwnershipTransferData.value().dstQueueIndex);
		}
		else
		{
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		}

		auto& window = _windowList.GetWindow(windowID);

		barrier.image = window.GetSwapchainImage(imagesIndex);
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		vkCmdPipelineBarrier(_buffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
	}

	void PrimaryNIRCommandBufferInternal::TransitionSwapchainImageToPresent(IDObject<VulkanSimplified::WindowPointer> windowID,
		std::optional<VulkanSimplified::QueueOwnershipTransferData> queueOwnershipTransferData, uint32_t imagesIndex)
	{
		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		if (queueOwnershipTransferData.has_value())
		{
			barrier.srcQueueFamilyIndex = _core.GetQueuesFamily(queueOwnershipTransferData.value().srcQueueIndex);
			barrier.dstQueueFamilyIndex = _core.GetQueuesFamily(queueOwnershipTransferData.value().dstQueueIndex);
		}
		else
		{
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		}

		auto& window = _windowList.GetWindow(windowID);

		barrier.image = window.GetSwapchainImage(imagesIndex);
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;

		vkCmdPipelineBarrier(_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
	}

	void PrimaryNIRCommandBufferInternal::BlitToSwapchainImage(IDObject<VulkanSimplified::WindowPointer> windowID, IDObject<AutoCleanupColorRenderTargetImage> imageID,
		uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, uint32_t swapchainImageIndex)
	{
		VkImageBlit blitData{};
		blitData.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		blitData.srcSubresource.mipLevel = 0;
		blitData.srcSubresource.baseArrayLayer = 0;
		blitData.srcSubresource.layerCount = 1;

		blitData.srcOffsets[0].x = static_cast<std::int32_t>(startX);
		blitData.srcOffsets[0].y = static_cast<std::int32_t>(startY);
		blitData.srcOffsets[0].z = 0;
		blitData.srcOffsets[1].x = static_cast<std::int32_t>(width);
		blitData.srcOffsets[1].y = static_cast<std::int32_t>(height);
		blitData.srcOffsets[1].z = 1;

		auto& window = _windowList.GetWindow(windowID);

		blitData.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		blitData.dstSubresource.mipLevel = 0;
		blitData.dstSubresource.baseArrayLayer = 0;
		blitData.dstSubresource.layerCount = 1;

		blitData.dstOffsets[0].x = 0;
		blitData.dstOffsets[0].y = 0;
		blitData.dstOffsets[0].z = 0;
		blitData.dstOffsets[1].x = static_cast<std::int32_t>(window.GetWidth());
		blitData.dstOffsets[1].y = static_cast<std::int32_t>(window.GetHeight());
		blitData.dstOffsets[1].z = 1;

		vkCmdBlitImage(_buffer, _imageList.GetColorRenderTargetImage(imageID), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, window.GetSwapchainImage(swapchainImageIndex), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1, &blitData, VK_FILTER_LINEAR);
	}
}