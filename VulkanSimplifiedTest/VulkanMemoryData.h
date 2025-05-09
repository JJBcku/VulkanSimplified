#pragma once
#include "pch.h"

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSDataBufferListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanMemoryData
{
	VulkanSimplified::MemoryAllocationFullID imageMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>> colorRenderTargetImages;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>> colorRenderTargetImageViews;

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer>> framebuffers;

	VulkanSimplified::MemoryAllocationFullID vertexMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer>> vertexBuffers;

	VulkanMemoryData() = default;
};