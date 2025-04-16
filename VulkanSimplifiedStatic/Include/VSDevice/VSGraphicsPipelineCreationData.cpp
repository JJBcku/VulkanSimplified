#include "VSDeviceIpch.h"
#include "VSGraphicsPipelineCreationData.h"

namespace VulkanSimplified
{
	GraphicsPipelineDerrivationData::GraphicsPipelineDerrivationData()
	{
		settings = PipelineDerrivationSettings::DO_NOT_DERRIVE;
	}

	ShaderSpecializationData::ShaderSpecializationData()
	{
		dataSize = std::numeric_limits<size_t>::max();
		data = nullptr;
	}

	GraphicsPipelineCreationData::GraphicsPipelineCreationData()
	{
		subpassIndex = std::numeric_limits<std::uint32_t>::max();
		padding = 0;
	}
}