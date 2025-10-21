#include "VSDeviceDNIpch.h"
#include "VSPrimaryIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	PrimaryIRCommandBufferInternal::PrimaryIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListsInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList,
		VkDevice device, VkCommandBuffer buffer, VkQueue queue) :
		PrimaryNIRCommandBufferInternal(core, deviceRenderPassData, sharedRenderPassData, devicePipelineData, synchronizationList, imageList, dataBufferList, windowList,
			descriptorDataList, device, buffer, queue)
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