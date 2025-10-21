#include "VSDeviceDNIpch.h"
#include "VSSecondaryIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	SecondaryIRCommandBufferInternal::SecondaryIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListsInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList,
		VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
		SecondaryNIRCommandBufferInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, dataBufferList, windowList,
			descriptorDataList, device, buffer, queue)
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