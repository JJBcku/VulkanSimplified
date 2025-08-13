#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSSecondaryNIRCommandBuffer.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSSecondaryNIRCommandBufferInternal.h"
#include "../../../DoNotInclude/DNIData/VSDevice/VSImageDataListsInternal.h"
#include "../../../DoNotInclude/DNIData/VSDevice/VSRenderPassDataListInternal.h"

namespace VulkanSimplified
{
	SecondaryNIRCommandBuffer::SecondaryNIRCommandBuffer(SecondaryNIRCommandBufferInternal& ref) : CommandBufferBase(ref), _internal(ref)
	{
	}

	SecondaryNIRCommandBuffer::~SecondaryNIRCommandBuffer()
	{
	}

	void SecondaryNIRCommandBuffer::BeginRecording(CommandBufferUsage usage, std::optional<std::pair<IDObject<AutoCleanupRenderPass>, uint32_t>> renderpass,
		std::optional<IDObject<AutoCleanupFramebuffer>> framebuffer, bool continueRenderPass)
	{
		_internal.BeginRecording(usage, renderpass, framebuffer, continueRenderPass);
	}

}