#pragma once

#include <memory>

namespace VulkanSimplified
{
	struct SharedDataListsCapacities;
}

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal;
	class SharedRenderPassDataListInternal;
	class SharedPipelineDataListInternal;

	class SharedDataMainListInternal
	{
	public:
		SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities);
		~SharedDataMainListInternal();

		SharedDescriptorDataListInternal& GetSharedDescriptorDataList();
		SharedRenderPassDataListInternal& GetSharedRenderPassDataList();
		SharedPipelineDataListInternal& GetPipelineDataList();

		const SharedDescriptorDataListInternal& GetSharedDescriptorDataList() const;
		const SharedRenderPassDataListInternal& GetSharedRenderPassDataList() const;
		const SharedPipelineDataListInternal& GetPipelineDataList() const;

	private:
		std::unique_ptr<SharedDescriptorDataListInternal> _descriptorData;
		std::unique_ptr<SharedRenderPassDataListInternal> _renderPassData;
		std::unique_ptr<SharedPipelineDataListInternal> _pipelineData;
	};
}