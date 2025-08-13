#include "VSDeviceDNIpch.h"
#include "VSSecondaryNIRCommandBufferInternal.h"

#include "VSRenderPassDataListInternal.h"
#include "VSImageDataListsInternal.h"

namespace VulkanSimplified
{
	SecondaryNIRCommandBufferInternal::SecondaryNIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList,
		VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
		CommandBufferBaseInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, dataBufferList, windowList,
			descriptorDataList, device, buffer, queue)
	{
	}

	SecondaryNIRCommandBufferInternal::~SecondaryNIRCommandBufferInternal()
	{
	}

	SecondaryNIRCommandBufferInternal::SecondaryNIRCommandBufferInternal(SecondaryNIRCommandBufferInternal&& rhs) noexcept : CommandBufferBaseInternal(std::move(rhs))
	{
	}

	void SecondaryNIRCommandBufferInternal::BeginRecording(CommandBufferUsage usage, const std::optional<std::pair<IDObject<AutoCleanupRenderPass>, uint32_t>>& renderpass,
		const std::optional<IDObject<AutoCleanupFramebuffer>>& framebuffer, bool continueRenderPass)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		switch (usage)
		{
		case CommandBufferUsage::MULTIPLE_USE_SIMULTANEOUS_USAGE:
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			break;
		case CommandBufferUsage::MULTIPLE_USE_NO_SIMULTANEOUS_USAGE:
			break;
		case CommandBufferUsage::ONE_USE:
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			break;
		default:
			throw std::runtime_error("PrimaryNIRCommandBufferInternal::BeginRecording Error: Program was giwen an erroneous command buffer usage value!");
		}

		if (continueRenderPass)
		{
			beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
		}

		VkCommandBufferInheritanceInfo inheritanceInfo{};
		inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		
		if (renderpass.has_value())
		{
			inheritanceInfo.renderPass = _deviceRenderPassData.GetRenderPass(renderpass.value().first);
			inheritanceInfo.subpass = renderpass.value().second;
		}

		if (framebuffer.has_value())
		{
			inheritanceInfo.framebuffer = _imageList.GetFramebuffer(framebuffer.value());
		}

		if (vkBeginCommandBuffer(_buffer, &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("PrimaryNIRCommandBufferInternal::BeginRecording Error: Program failed to begin a command buffer's recording session!");
	}

}