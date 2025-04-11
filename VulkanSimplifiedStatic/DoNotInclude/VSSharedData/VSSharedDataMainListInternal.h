#pragma once

#include "VSSharedPipelineDataListInternal.h"
#include "VSSharedDescriptorDataListInternal.h"

namespace VulkanSimplified
{
	struct SharedDataListsCapacities;
}

namespace VulkanSimplifiedInternal
{
	class SharedDataMainListInternal
	{
	public:
		SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities);
		~SharedDataMainListInternal();

		SharedDescriptorDataListInternal& GetDescriptorDataList();
		SharedPipelineDataListInternal& GetPipelineDataList();

		const SharedDescriptorDataListInternal& GetDescriptorDataList() const;
		const SharedPipelineDataListInternal& GetPipelineDataList() const;

	private:
		SharedDescriptorDataListInternal _descriptorData;
		SharedPipelineDataListInternal _pipelineData;
	};
}