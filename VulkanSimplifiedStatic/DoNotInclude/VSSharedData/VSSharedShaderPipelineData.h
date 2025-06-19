#pragma once

#include <vulkan/vulkan_core.h>
#include <stdint.h>
#include <string>
#include <compare>

namespace VulkanSimplifiedInternal
{
	struct SharedShaderPipelineData
	{
		VkShaderStageFlagBits shaderStage;
		uint32_t padding;
		std::string entryPointName;

		SharedShaderPipelineData();

		bool operator==(const SharedShaderPipelineData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const SharedShaderPipelineData& rhs) const noexcept = default;
	};
}