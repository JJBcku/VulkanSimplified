#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedPipelineDataListsCapacities.h"

namespace VulkanSimplified
{
	SharedPipelineDataListsssCapacities::SharedPipelineDataListsssCapacities()
	{
		initialSpecializationElementsCapacity = 0;
		initialShaderPipelineInfoCapacity = 0;

		initialVertexAttributeInfoCapacity = 0;
		initialVertexBindingInfoCapacity = 0;
		initialVertexInputPipelineInfoCapacity = 0;

		initialPipelineScissorDataCapacity = 0;
		initialPipelineViewportDataCapacity = 0;

		initialPipelineInputAssemblyInfoCapacity = 0;
		initialPipelineRasterizationInfoCapacity = 0;
		initialPipelineMultisampleInfoCapacity = 0;
		initialPipelineDepthStencilInfoCapacity = 0;
		initialPipelineColorBlendAttachmentInfoCapacity = 0;

		initialPushConstantDataCapacity = 0;
	}
}