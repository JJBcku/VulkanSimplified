#pragma once

namespace VulkanSimplifiedInternal
{
	struct PipelineMultisampleData
	{
		VkSampleCountFlagBits sampleCount;
		VkBool32 sampleShadingEnable;
		float minSampleShading;
		uint32_t padding;

		PipelineMultisampleData();

		bool operator==(const PipelineMultisampleData& rhs) const noexcept = default;
		std::partial_ordering operator<=>(const PipelineMultisampleData& rhs) const noexcept = default;
	};
}