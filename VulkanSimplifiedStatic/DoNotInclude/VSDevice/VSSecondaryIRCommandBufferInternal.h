#pragma once

#include "VSSecondaryNIRCommandBufferInternal.h"

namespace VulkanSimplifiedInternal
{
	class SecondaryIRCommandBufferInternal : public SecondaryNIRCommandBufferInternal
	{
	public:
		SecondaryIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList,
			WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue);
		~SecondaryIRCommandBufferInternal();

		SecondaryIRCommandBufferInternal(const SecondaryIRCommandBufferInternal&) noexcept = delete;
		SecondaryIRCommandBufferInternal(SecondaryIRCommandBufferInternal&& rhs) noexcept;

		SecondaryIRCommandBufferInternal& operator=(const SecondaryIRCommandBufferInternal&) noexcept = delete;
		SecondaryIRCommandBufferInternal& operator=(SecondaryIRCommandBufferInternal&& rhs) noexcept = delete;

		void ResetCommandBuffer(bool freeResources);
	};
}