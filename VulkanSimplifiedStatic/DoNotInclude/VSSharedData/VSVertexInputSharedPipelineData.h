#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	struct VertexBindingDescriptionData;

	struct VertexInputSharedPipelineData
	{
		std::vector<IDObject<VertexBindingDescriptionData>> vertexBindings;

		VertexInputSharedPipelineData() = default;

		bool operator==(const VertexInputSharedPipelineData& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const VertexInputSharedPipelineData& rhs) const noexcept = default;
	};
}