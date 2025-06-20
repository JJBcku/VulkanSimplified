#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSPipelineDataLists.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSPipelineDataListsInternal.h"

namespace VulkanSimplified
{
	PipelineDataLists::PipelineDataLists(PipelineDataListsInternal& ref) : _internal(ref)
	{
	}

	PipelineDataLists::~PipelineDataLists()
	{
	}

	IDObject<AutoCleanupPipelineLayout> PipelineDataLists::AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving)
	{
		return _internal.AddPipelineLayout(creationData, addOnReserving);
	}

	std::vector<IDObject<AutoCleanupGraphicsPipeline>> PipelineDataLists::AddGraphicPipelines(
		const std::vector<GraphicsPipelineCreationData>& creationDataList, size_t addOnReserving)
	{
		return _internal.AddGraphicPipelines(creationDataList, addOnReserving);
	}

}