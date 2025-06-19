#pragma once

#include <vulkan/vulkan_core.h>
#include <compare>

namespace VulkanSimplifiedInternal
{
	struct PipelineInputAssemblyData
	{
		VkPrimitiveTopology topology;
		VkBool32 primitiveRestartEnable;

		PipelineInputAssemblyData();

		bool operator==(const PipelineInputAssemblyData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const PipelineInputAssemblyData& rhs) const noexcept = default;
	};
}