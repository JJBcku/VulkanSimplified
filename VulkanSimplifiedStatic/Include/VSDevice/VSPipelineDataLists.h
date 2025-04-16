#pragma once

template<class T>
class IDObject;

namespace VulkanSimplifiedInternal
{
	class PipelineDataListsInternal;
	class AutoCleanupPipelineLayout;
}

namespace VulkanSimplified
{
	struct PipelineLayoutCreationData;

	class PipelineDataLists
	{
	public:
		PipelineDataLists(VulkanSimplifiedInternal::PipelineDataListsInternal& ref);
		~PipelineDataLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::PipelineDataListsInternal& _internal;
	};
}