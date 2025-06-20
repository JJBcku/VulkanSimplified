#pragma once
#include "pch.h"

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSDataBufferListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanMemoryData
{
	VulkanSimplified::MemoryAllocationFullID imageMemoryAllocation;
	std::vector<IDObject<VulkanSimplified::AutoCleanupColorRenderTargetImage>> colorRenderTargetImages;
	std::vector<IDObject<VulkanSimplified::AutoCleanupImageView>> colorRenderTargetImageViews;
	std::vector<IDObject<VulkanSimplified::AutoCleanupDepthStencilRenderTargetImage>> depthRenderTargetImages;
	std::vector<IDObject<VulkanSimplified::AutoCleanupImageView>> depthRenderTargetImageViews;
	std::vector<IDObject<VulkanSimplified::AutoCleanupResolveRenderTargetImage>> resolveRenderTargetImages;
	std::vector<IDObject<VulkanSimplified::AutoCleanupImageView>> resolveRenderTargetImageViews;

	std::vector<IDObject<VulkanSimplified::AutoCleanupFramebuffer>> framebuffers;

	VulkanSimplified::MemoryAllocationFullID vertexMemoryAllocation;
	std::vector<IDObject<VulkanSimplified::AutoCleanupVertexBuffer>> vertexBuffers;

	VulkanSimplified::MemoryAllocationFullID indexMemoryAllocation;
	std::vector<IDObject<VulkanSimplified::AutoCleanupIndexBuffer>> indexBuffers;

	VulkanSimplified::MemoryAllocationFullID uniformMemoryAllocation;
	std::vector<IDObject<VulkanSimplified::AutoCleanupUniformBuffer>> uniformBuffers;

	VulkanSimplified::MemoryAllocationFullID stagingMemoryAllocation;
	std::vector<IDObject<VulkanSimplified::AutoCleanupStagingBuffer>> stagingBuffers;

	bool vertexMemoryMapped = false;
	bool indexMemoryMapped = false;
	bool uniformMemoryMapped = false;

	VulkanMemoryData() = default;
};