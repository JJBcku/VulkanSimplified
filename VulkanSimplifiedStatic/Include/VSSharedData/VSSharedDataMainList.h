#pragma once

namespace VulkanSimplifiedInternal
{
	class SharedDataMainListInternal;
}

namespace VulkanSimplified
{
	class SharedPipelineDataList;

	class SharedDataMainList
	{
	public:
		SharedDataMainList(VulkanSimplifiedInternal::SharedDataMainListInternal& ref);
		~SharedDataMainList();

		SharedPipelineDataList GetSharedPipelineDataList();

		const SharedPipelineDataList GetSharedPipelineDataList() const;

	private:
		VulkanSimplifiedInternal::SharedDataMainListInternal& _internal;
	};
}