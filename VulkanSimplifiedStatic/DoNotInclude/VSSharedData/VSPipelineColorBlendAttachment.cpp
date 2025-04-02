#include "VSSharedNIpch.h"
#include "VSPipelineColorBlendAttachment.h"

namespace VulkanSimplifiedInternal
{
	PipelineColorBlendAttachment::PipelineColorBlendAttachment()
	{
		blendEnable = static_cast<VkBool32>(std::numeric_limits<std::uint32_t>::max());
		srcColorBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
		dstColorBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
		colorBlendOp = static_cast<VkBlendOp>(std::numeric_limits<std::uint32_t>::max());
		srcAlphaBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
		dstAlphaBlend = static_cast<VkBlendFactor>(std::numeric_limits<std::uint32_t>::max());
		alphaBlendOp = static_cast<VkBlendOp>(std::numeric_limits<std::uint32_t>::max());
		colorWriteMask = static_cast<VkColorComponentFlags>(std::numeric_limits<std::uint32_t>::max());
	}
}