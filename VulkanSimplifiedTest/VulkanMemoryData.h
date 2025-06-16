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
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDepthStencilRenderTargetImage>> depthRenderTargetImages;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>> depthRenderTargetImageViews;

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer>> framebuffers;

	VulkanSimplified::MemoryAllocationFullID vertexMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer>> vertexBuffers;

	VulkanSimplified::MemoryAllocationFullID indexMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer>> indexBuffers;

	VulkanSimplified::MemoryAllocationFullID uniformMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer>> uniformBuffers;

	VulkanSimplified::MemoryAllocationFullID stagingMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer>> stagingBuffers;

	bool vertexMemoryMapped = false;
	bool indexMemoryMapped = false;
	bool uniformMemoryMapped = false;

	VulkanMemoryData() = default;
};