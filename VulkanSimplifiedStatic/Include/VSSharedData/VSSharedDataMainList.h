#pragma once

namespace VulkanSimplifiedInternal
{
	class SharedDataMainListInternal;
}

namespace VulkanSimplified
{
	class SharedDescriptorDataList;
	class SharedPipelineDataList;

	class SharedDataMainList
	{
	public:
		SharedDataMainList(VulkanSimplifiedInternal::SharedDataMainListInternal& ref);
		~SharedDataMainList();

		SharedDescriptorDataList GetDescriptorDataList();
		SharedPipelineDataList GetSharedPipelineDataList();

		const SharedDescriptorDataList GetDescriptorDataList() const;
		const SharedPipelineDataList GetSharedPipelineDataList() const;

	private:
		VulkanSimplifiedInternal::SharedDataMainListInternal& _internal;
	};
}