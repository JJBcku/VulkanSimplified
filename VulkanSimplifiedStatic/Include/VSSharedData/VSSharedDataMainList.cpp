#include "VSSharedIpch.h"
#include "VSSharedDataMainList.h"

#include "VSSharedPipelineDataList.h"

#include "../../DoNotInclude/VSSharedData/VSSharedDataMainListInternal.h"
#include "../../DoNotInclude/VSSharedData/VSSharedPipelineDataListInternal.h"

namespace VulkanSimplified
{
	SharedDataMainList::SharedDataMainList(VulkanSimplifiedInternal::SharedDataMainListInternal& ref) : _internal(ref)
	{
	}

	SharedDataMainList::~SharedDataMainList()
	{
	}

	SharedPipelineDataList SharedDataMainList::GetSharedPipelineDataList()
	{
		return _internal.GetPipelineDataList();
	}

	const SharedPipelineDataList SharedDataMainList::GetSharedPipelineDataList() const
	{
		return _internal.GetPipelineDataList();
	}

}