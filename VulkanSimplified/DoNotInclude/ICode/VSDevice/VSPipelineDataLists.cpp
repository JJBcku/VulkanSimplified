#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSPipelineDataLists.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSPipelineDataListsInternal.h"

namespace VulkanSimplified
{
	PipelineDataLists::PipelineDataLists(PipelineDataListsInternal& ref) : _internal(ref)
	{
	}

	PipelineDataLists::~PipelineDataLists()
	{
	}

	std::optional<IDObject<AutoCleanupPipelineCache>> PipelineDataLists::AddPipelineCache(const std::vector<unsigned char>& initialData, size_t addOnReserving)
	{
		return _internal.AddPipelineCache(initialData, addOnReserving);
	}

	IDObject<AutoCleanupPipelineLayout> PipelineDataLists::AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving)
	{
		return _internal.AddPipelineLayout(creationData, addOnReserving);
	}

	std::vector<IDObject<AutoCleanupGraphicsPipeline>> PipelineDataLists::AddGraphicPipelines(
		const std::vector<GraphicsPipelineCreationData>& creationDataList, std::optional<IDObject<AutoCleanupPipelineCache>> pipelineCacheID, size_t addOnReserving)
	{
		return _internal.AddGraphicPipelines(creationDataList, pipelineCacheID, addOnReserving);
	}

	size_t PipelineDataLists::GetPipelineCacheSize(IDObject<AutoCleanupPipelineCache> cacheID) const
	{
		return _internal.GetPipelineCacheSize(cacheID);
	}

	std::vector<unsigned char> PipelineDataLists::GetPipelineCacheData(IDObject<AutoCleanupPipelineCache> cacheID) const
	{
		return _internal.GetPipelineCacheData(cacheID);
	}

}