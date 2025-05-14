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

	SharedDescriptorDataList SharedDataMainList::GetSharedDescriptorDataList()
	{
		return _internal.GetSharedDescriptorDataList();
	}

	SharedRenderPassDataList SharedDataMainList::GetSharedRenderPassDataList()
	{
		return _internal.GetSharedRenderPassDataList();
	}

	SharedPipelineDataListss SharedDataMainList::GetSharedPipelineDataListss()
	{
		return _internal.GetPipelineDataList();
	}

	const SharedDescriptorDataList SharedDataMainList::GetSharedDescriptorDataList() const
	{
		return _internal.GetSharedDescriptorDataList();
	}

	const SharedRenderPassDataList SharedDataMainList::GetSharedRenderPassDataList() const
	{
		return _internal.GetSharedRenderPassDataList();
	}

	const SharedPipelineDataListss SharedDataMainList::GetSharedPipelineDataListss() const
	{
		return _internal.GetPipelineDataList();
	}

}