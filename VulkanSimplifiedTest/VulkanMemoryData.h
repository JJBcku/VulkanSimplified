#pragma once
#include "pch.h"

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>

namespace VulkanSimplifiedInternal
{
	class AutoCleanupColorRenderTargetImage;
	class AutoCleanupImageView;
}

struct VulkanMemoryData
{
	VulkanSimplified::MemoryAllocationFullID imageMemoryAllocation;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>> colorRenderTargetImages;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>> colorRenderTargetImageViews;

	VulkanMemoryData() = default;
};