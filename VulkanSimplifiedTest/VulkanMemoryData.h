#pragma once
#include "pch.h"

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSDataBufferListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanMemoryData
{
	VS::MemoryAllocationFullID imageMemoryAllocation;
	std::vector<IDObject<VS::AutoCleanupColorRenderTargetImage>> colorRenderTargetImages;
	std::vector<IDObject<VS::AutoCleanupImageView>> colorRenderTargetImageViews;
	std::vector<IDObject<VS::AutoCleanupDepthStencilRenderTargetImage>> depthRenderTargetImages;
	std::vector<IDObject<VS::AutoCleanupImageView>> depthRenderTargetImageViews;
	std::vector<IDObject<VS::AutoCleanupResolveRenderTargetImage>> resolveRenderTargetImages;
	std::vector<IDObject<VS::AutoCleanupImageView>> resolveRenderTargetImageViews;

	std::vector<IDObject<VS::AutoCleanupFramebuffer>> framebuffers;

	VS::MemoryAllocationFullID vertexMemoryAllocation;
	std::vector<IDObject<VS::AutoCleanupVertexBuffer>> vertexBuffers;

	VS::MemoryAllocationFullID indexMemoryAllocation;
	std::vector<IDObject<VS::AutoCleanupIndexBuffer>> indexBuffers;

	VS::MemoryAllocationFullID uniformMemoryAllocation;
	std::vector<IDObject<VS::AutoCleanupUniformBuffer>> uniformBuffers;

	VS::MemoryAllocationFullID stagingMemoryAllocation;
	std::vector<IDObject<VS::AutoCleanupStagingBuffer>> stagingBuffers;

	bool vertexMemoryMapped = false;
	bool indexMemoryMapped = false;
	bool uniformMemoryMapped = false;

	VulkanMemoryData() = default;
};