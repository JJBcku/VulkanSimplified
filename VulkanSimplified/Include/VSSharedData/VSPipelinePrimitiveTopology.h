#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
	enum class PipelinePrimitiveTopology : uint64_t
	{
		POINT_LIST = 0,
		LINE_LIST = 1,
		LINE_STRIP = 2,
		TRIANGLE_LIST = 3,
		TRIANGLE_STRIP = 4,
		TRIANGLE_FAN = 5,
		LINE_LIST_WITH_ADJACENCY = 6,
		LINE_STRIP_WITH_ADJACENCY = 7,
		TRIANGLE_LIST_WITH_ADJACENCY = 8,
		TRIANGLE_STRIP_WITH_ADJACENCY = 9,
		PATCH_LIST = 10,
	};
}