#include "VSDeviceIpch.h"
#include "VSPipelineDataLists.h"

#include "../../DoNotInclude/VSDevice/VSPipelineDataListsInternal.h"

namespace VulkanSimplified
{
	PipelineDataLists::PipelineDataLists(VulkanSimplifiedInternal::PipelineDataListsInternal& ref) : _internal(ref)
	{
	}

	PipelineDataLists::~PipelineDataLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> PipelineDataLists::AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving)
	{
		return _internal.AddPipelineLayout(creationData, addOnReserving);
	}

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline>> PipelineDataLists::AddGraphicPipelines(
		const std::vector<GraphicsPipelineCreationData>& creationDataList, size_t addOnReserving)
	{
		return _internal.AddGraphicPipelines(creationDataList, addOnReserving);
	}

}