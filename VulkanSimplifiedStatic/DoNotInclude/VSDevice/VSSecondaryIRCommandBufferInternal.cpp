#include "VSDeviceNIpch.h"
#include "VSSecondaryIRCommandBufferInternal.h"

namespace VulkanSimplifiedInternal
{
	SecondaryIRCommandBufferInternal::SecondaryIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		const ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
		SecondaryNIRCommandBufferInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, dataBufferList, windowList,
			device, buffer, queue)
	{
	}

	SecondaryIRCommandBufferInternal::~SecondaryIRCommandBufferInternal()
	{
	}

	SecondaryIRCommandBufferInternal::SecondaryIRCommandBufferInternal(SecondaryIRCommandBufferInternal&& rhs) noexcept : SecondaryNIRCommandBufferInternal(std::move(rhs))
	{
	}

	void SecondaryIRCommandBufferInternal::ResetCommandBuffer(bool freeResources)
	{
		VkCommandBufferResetFlags flags = 0;
		if (freeResources)
			flags = VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT;

		vkResetCommandBuffer(_buffer, flags);
	}

}