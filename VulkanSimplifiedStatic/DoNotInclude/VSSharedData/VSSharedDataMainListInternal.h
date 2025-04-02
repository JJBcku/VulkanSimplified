#pragma once

#include "VSSharedPipelineDataListInternal.h"

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

		SharedPipelineDataListInternal& GetPipelineDataList();

		const SharedPipelineDataListInternal& GetPipelineDataList() const;

	private:
		SharedPipelineDataListInternal _pipelineData;
	};
}