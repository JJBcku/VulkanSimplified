#pragma once

#include <vulkan/vulkan_core.h>
#include <compare>

namespace VulkanSimplifiedInternal
{
	struct PipelineColorBlendAttachment
	{
		VkBool32 blendEnable;
		VkBlendFactor srcColorBlend;
		VkBlendFactor dstColorBlend;
		VkBlendOp colorBlendOp;
		VkBlendFactor srcAlphaBlend;
		VkBlendFactor dstAlphaBlend;
		VkBlendOp alphaBlendOp;
		VkColorComponentFlags colorWriteMask;

		PipelineColorBlendAttachment();

		bool operator==(const PipelineColorBlendAttachment& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const PipelineColorBlendAttachment& rhs) const noexcept = default;
	};
}