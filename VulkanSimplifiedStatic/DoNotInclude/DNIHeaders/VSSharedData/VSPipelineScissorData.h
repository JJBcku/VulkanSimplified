#pragma once

#include <stdint.h>
#include <compare>

namespace VulkanSimplified
{
	struct PipelineScissorData
	{
		int32_t offsetX;
		int32_t offsetY;
		uint32_t width;
		uint32_t height;

		PipelineScissorData();

		bool operator==(const PipelineScissorData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const PipelineScissorData& rhs) const noexcept = default;
	};
}