#include "VSSharedNIpch.h"
#include "VSSharedDataMainListInternal.h"

#include "../../Include/VSSharedData/VSSharedDataListsCapacities.h"

namespace VulkanSimplifiedInternal
{
	SharedDataMainListInternal::SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities) : _pipelineData(initialCapabilities.pipelineLists)
	{
	}

	SharedDataMainListInternal::~SharedDataMainListInternal()
	{
	}

	SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList()
	{
		return _pipelineData;
	}

	const SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList() const
	{
		return _pipelineData;
	}

}