#include "VSDeviceNIpch.h"
#include "VSSecondaryNIRCommandBufferInternal.h"

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

}