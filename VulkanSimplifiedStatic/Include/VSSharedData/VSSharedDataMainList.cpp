#include "VSSharedIpch.h"
#include "VSSharedDataMainList.h"

#include "VSSharedPipelineDataList.h"
#include "VSSharedDescriptorDataList.h"

#include "../../DoNotInclude/VSSharedData/VSSharedDataMainListInternal.h"
#include "../../DoNotInclude/VSSharedData/VSSharedDescriptorDataListInternal.h"
#include "../../DoNotInclude/VSSharedData/VSSharedPipelineDataListInternal.h"

namespace VulkanSimplified
{
	SharedDataMainList::SharedDataMainList(VulkanSimplifiedInternal::SharedDataMainListInternal& ref) : _internal(ref)
	{
	}

	SharedDataMainList::~SharedDataMainList()
	{
	}

	SharedDescriptorDataList SharedDataMainList::GetDescriptorDataList()
	{
		return _internal.GetDescriptorDataList();
	}

	SharedPipelineDataList SharedDataMainList::GetSharedPipelineDataList()
	{
		return _internal.GetPipelineDataList();
	}

	const SharedDescriptorDataList SharedDataMainList::GetDescriptorDataList() const
	{
		return _internal.GetDescriptorDataList();
	}

	const SharedPipelineDataList SharedDataMainList::GetSharedPipelineDataList() const
	{
		return _internal.GetPipelineDataList();
	}

}