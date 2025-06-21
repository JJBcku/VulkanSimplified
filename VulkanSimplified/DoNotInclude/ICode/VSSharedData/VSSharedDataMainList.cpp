#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedDataMainList.h"

#include "../../../Include/VSSharedData/VSSharedDescriptorDataList.h"
#include "../../../Include/VSSharedData/VSSharedRenderPassDataList.h"
#include "../../../Include/VSSharedData/VSSharedPipelineDataLists.h"

#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedDataMainListInternal.h"
#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedDescriptorDataListInternal.h"
#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedRenderPassDataInternal.h"
#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedPipelineDataListsInternal.h"

namespace VulkanSimplified
{
	SharedDataMainList::SharedDataMainList(SharedDataMainListInternal& ref) : _internal(ref)
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

	SharedPipelineDataList SharedDataMainList::GetSharedPipelineDataListss()
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

	const SharedPipelineDataList SharedDataMainList::GetSharedPipelineDataListss() const
	{
		return _internal.GetPipelineDataList();
	}

}