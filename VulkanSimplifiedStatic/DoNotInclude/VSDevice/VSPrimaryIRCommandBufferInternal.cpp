#include "VSDeviceNIpch.h"
#include "VSPrimaryIRCommandBufferInternal.h"

namespace VulkanSimplifiedInternal
{
	PrimaryIRCommandBufferInternal::PrimaryIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		const ImageDataListsInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
		PrimaryNIRCommandBufferInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, windowList, device, buffer, queue)
	{
	}

	PrimaryIRCommandBufferInternal::~PrimaryIRCommandBufferInternal()
	{
	}

	PrimaryIRCommandBufferInternal::PrimaryIRCommandBufferInternal(PrimaryIRCommandBufferInternal&& rhs) noexcept : PrimaryNIRCommandBufferInternal(std::move(rhs))
	{
	}

	void PrimaryIRCommandBufferInternal::ResetCommandBuffer(bool freeResources)
	{
		VkCommandBufferResetFlags flags = 0;
		if (freeResources)
			flags = VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT;

		vkResetCommandBuffer(_buffer, flags);
	}

}