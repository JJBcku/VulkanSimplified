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

		SharedDescriptorDataList GetDescriptorDataList();
		SharedRenderPassDataList GetRenderPassDataList();
		SharedPipelineDataList GetSharedPipelineDataList();

		const SharedDescriptorDataList GetDescriptorDataList() const;
		const SharedRenderPassDataList GetRenderPassDataList() const;
		const SharedPipelineDataList GetSharedPipelineDataList() const;

	private:
		VulkanSimplifiedInternal::SharedDataMainListInternal& _internal;
	};
}