#pragma once

#include "VSCommandBufferBaseInternal.h"

namespace VulkanSimplifiedInternal
{
	class SecondaryNIRCommandBufferInternal : public CommandBufferBaseInternal
	{
	public:
		SecondaryNIRCommandBufferInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
			const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData,
			const SynchronizationDataListsInternal& synchronizationList, const ImageDataListsInternal& imageList, WindowListInternal& windowList,
			VkDevice device, VkCommandBuffer buffer, VkQueue queue);
		~SecondaryNIRCommandBufferInternal();

		SecondaryNIRCommandBufferInternal(const SecondaryNIRCommandBufferInternal&) noexcept = delete;
		SecondaryNIRCommandBufferInternal(SecondaryNIRCommandBufferInternal&& rhs) noexcept;

		SecondaryNIRCommandBufferInternal& operator=(const SecondaryNIRCommandBufferInternal&) noexcept = delete;
		SecondaryNIRCommandBufferInternal& operator=(SecondaryNIRCommandBufferInternal&& rhs) noexcept = delete;
	};
}