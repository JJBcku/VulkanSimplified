#pragma once
#include "pch.h"

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSImageDataListsDef.h>

struct VulkanMemoryData
{
	VulkanSimplified::MemoryAllocationFullID imageMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>> colorRenderTargetImages;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>> colorRenderTargetImageViews;

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer>> framebuffers;

	VulkanMemoryData() = default;
};