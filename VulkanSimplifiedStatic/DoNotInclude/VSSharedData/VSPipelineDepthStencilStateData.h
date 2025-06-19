#pragma once

#include <vulkan/vulkan_core.h>
#include <compare>
#include <stdint.h>

namespace VulkanSimplifiedInternal
{
	struct PipelineDepthStencilStateData
	{
		VkBool32 depthTestEnable;
		VkBool32 depthWriteEnable;
		VkCompareOp compareOp;
		float minDepth;
		float maxDepth;
		uint32_t padding;

		PipelineDepthStencilStateData();

		bool operator==(const PipelineDepthStencilStateData& rhs) const noexcept = default;
		std::partial_ordering operator<=>(const PipelineDepthStencilStateData& rhs) const noexcept = default;
	};
}