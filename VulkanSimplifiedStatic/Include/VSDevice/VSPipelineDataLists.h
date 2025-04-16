#pragma once

template<class T>
class IDObject;

namespace VulkanSimplifiedInternal
{
	class PipelineDataListsInternal;
	class AutoCleanupPipelineLayout;
	class AutoCleanupGraphicsPipeline;
}

namespace VulkanSimplified
{
	struct PipelineLayoutCreationData;
	struct GraphicsPipelineCreationData;

	class PipelineDataLists
	{
	public:
		PipelineDataLists(VulkanSimplifiedInternal::PipelineDataListsInternal& ref);
		~PipelineDataLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving = 0);
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline>> AddGraphicPipelines(const std::vector<GraphicsPipelineCreationData>& creationDataList,
			size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::PipelineDataListsInternal& _internal;
	};
}