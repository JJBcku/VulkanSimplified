#pragma once

#include "VSCommandBufferBaseInternal.h"

#include <optional>

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

		void BeginRecording(CommandBufferUsage usage, const std::optional<std::pair<IDObject<AutoCleanupRenderPass>, uint32_t>>& renderpass,
			const std::optional<IDObject<AutoCleanupFramebuffer>>& framebuffer, bool continueRenderPass);
	};
}