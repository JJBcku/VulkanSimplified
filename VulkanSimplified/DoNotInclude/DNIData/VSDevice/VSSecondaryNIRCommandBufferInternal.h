#pragma once

#include "VSCommandBufferBaseInternal.h"

namespace VulkanSimplified
{
	class SecondaryNIRCommandBufferInternal : public CommandBufferBaseInternal
	{
	public:
		SecondaryNIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
		~SecondaryNIRCommandBufferInternal();

		SecondaryNIRCommandBufferInternal(const SecondaryNIRCommandBufferInternal&) noexcept = delete;
		SecondaryNIRCommandBufferInternal(SecondaryNIRCommandBufferInternal&& rhs) noexcept;

		SecondaryNIRCommandBufferInternal& operator=(const SecondaryNIRCommandBufferInternal&) noexcept = delete;
		SecondaryNIRCommandBufferInternal& operator=(SecondaryNIRCommandBufferInternal&& rhs) noexcept = delete;
	};
}