#pragma once

namespace VulkanSimplifiedInternal
{
	class SharedDataMainListInternal;
}

namespace VulkanSimplified
{
	class SharedDescriptorDataList;
	class SharedRenderPassDataList;
	class SharedPipelineDataListss;

	class SharedDataMainList
	{
	public:
		SharedDataMainList(VulkanSimplifiedInternal::SharedDataMainListInternal& ref);
		~SharedDataMainList();

		SharedDescriptorDataList GetSharedDescriptorDataList();
		SharedRenderPassDataList GetSharedRenderPassDataList();
		SharedPipelineDataListss GetSharedPipelineDataListss();

		const SharedDescriptorDataList GetSharedDescriptorDataList() const;
		const SharedRenderPassDataList GetSharedRenderPassDataList() const;
		const SharedPipelineDataListss GetSharedPipelineDataListss() const;

	private:
		VulkanSimplifiedInternal::SharedDataMainListInternal& _internal;
	};
}