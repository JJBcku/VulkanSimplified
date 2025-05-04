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

		SharedDescriptorDataList GetDescriptorDataList();
		SharedRenderPassDataList GetRenderPassDataList();
		SharedPipelineDataListss GetSharedPipelineDataListss();

		const SharedDescriptorDataList GetDescriptorDataList() const;
		const SharedRenderPassDataList GetRenderPassDataList() const;
		const SharedPipelineDataListss GetSharedPipelineDataListss() const;

	private:
		VulkanSimplifiedInternal::SharedDataMainListInternal& _internal;
	};
}