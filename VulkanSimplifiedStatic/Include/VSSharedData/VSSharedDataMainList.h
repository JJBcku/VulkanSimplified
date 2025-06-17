#pragma once

namespace VulkanSimplifiedInternal
{
	class SharedDataMainListInternal;
}

namespace VulkanSimplified
{
	class SharedDescriptorDataList;
	class SharedRenderPassDataList;
	class SharedPipelineDataList;

	class SharedDataMainList
	{
	public:
		SharedDataMainList(VulkanSimplifiedInternal::SharedDataMainListInternal& ref);
		~SharedDataMainList();

		SharedDescriptorDataList GetSharedDescriptorDataList();
		SharedRenderPassDataList GetSharedRenderPassDataList();
		SharedPipelineDataList GetSharedPipelineDataListss();

		const SharedDescriptorDataList GetSharedDescriptorDataList() const;
		const SharedRenderPassDataList GetSharedRenderPassDataList() const;
		const SharedPipelineDataList GetSharedPipelineDataListss() const;

	private:
		VulkanSimplifiedInternal::SharedDataMainListInternal& _internal;
	};
}