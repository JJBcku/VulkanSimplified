#pragma once

#include <vulkan/vulkan_core.h>
#include <compare>
#include <stdint.h>

namespace VulkanSimplifiedInternal
{
	struct PipelineRasterizationData
	{
		VkPolygonMode polygonMode;
		VkCullModeFlagBits cullMode;
		VkFrontFace frontFace;
		uint32_t padding;

		PipelineRasterizationData();

		bool operator==(const PipelineRasterizationData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const PipelineRasterizationData& rhs) const noexcept = default;
	};
}