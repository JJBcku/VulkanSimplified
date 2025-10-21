#pragma once

#include <memory>

namespace VulkanSimplified
{
	struct SharedDataListsCapacities;
}

namespace VulkanSimplified
{
	class SharedDescriptorDataListInternal;
	class SharedRenderPassDataListsInternal;
	class SharedPipelineDataListsInternal;

	class SharedDataMainListInternal
	{
	public:
		SharedDataMainListInternal(const SharedDataListsCapacities& initialCapabilities);
		~SharedDataMainListInternal();

		SharedDescriptorDataListInternal& GetSharedDescriptorDataList();
		SharedRenderPassDataListsInternal& GetSharedRenderPassDataLists();
		SharedPipelineDataListsInternal& GetPipelineDataLists();

		const SharedDescriptorDataListInternal& GetSharedDescriptorDataList() const;
		const SharedRenderPassDataListsInternal& GetSharedRenderPassDataLists() const;
		const SharedPipelineDataListsInternal& GetPipelineDataLists() const;

	private:
		std::unique_ptr<SharedDescriptorDataListInternal> _descriptorData;
		std::unique_ptr<SharedRenderPassDataListsInternal> _renderPassData;
		std::unique_ptr<SharedPipelineDataListsInternal> _pipelineData;
	};
}