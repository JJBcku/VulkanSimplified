#include "VSSharedIpch.h"
#include "VSSharedDataMainList.h"

#include "VSSharedDescriptorDataList.h"
#include "VSSharedRenderPassDataList.h"
#include "VSSharedPipelineDataLists.h"

#include "../../DoNotInclude/VSSharedData/VSSharedDataMainListInternal.h"
#include "../../DoNotInclude/VSSharedData/VSSharedDescriptorDataListInternal.h"
#include "../../DoNotInclude/VSSharedData/VSSharedRenderPassDataInternal.h"
#include "../../DoNotInclude/VSSharedData/VSSharedPipelineDataListsInternal.h"

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

	SharedRenderPassDataList SharedDataMainList::GetRenderPassDataList()
	{
		return _internal.GetRenderPassDataList();
	}

	SharedPipelineDataListss SharedDataMainList::GetSharedPipelineDataListss()
	{
		return _internal.GetPipelineDataList();
	}

	const SharedDescriptorDataList SharedDataMainList::GetDescriptorDataList() const
	{
		return _internal.GetDescriptorDataList();
	}

	const SharedRenderPassDataList SharedDataMainList::GetRenderPassDataList() const
	{
		return _internal.GetRenderPassDataList();
	}

	const SharedPipelineDataListss SharedDataMainList::GetSharedPipelineDataListss() const
	{
		return _internal.GetPipelineDataList();
	}

}