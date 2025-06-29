#pragma once

#include "VSPrimaryNIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	class PrimaryIRCommandBufferInternal : public PrimaryNIRCommandBufferInternal
	{
	public:
		PrimaryIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
		~PrimaryIRCommandBufferInternal();

		PrimaryIRCommandBufferInternal(const PrimaryIRCommandBufferInternal&) noexcept = delete;
		PrimaryIRCommandBufferInternal(PrimaryIRCommandBufferInternal&& rhs) noexcept;

		PrimaryIRCommandBufferInternal& operator=(const PrimaryIRCommandBufferInternal&) noexcept = delete;
		PrimaryIRCommandBufferInternal& operator=(PrimaryIRCommandBufferInternal&& rhs) noexcept = delete;

		void ResetCommandBuffer(bool freeResources);
	};
}