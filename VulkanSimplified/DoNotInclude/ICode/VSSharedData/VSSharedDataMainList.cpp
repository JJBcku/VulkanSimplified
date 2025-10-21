#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedDataMainList.h"

#include "../../../Include/VSSharedData/VSSharedDescriptorDataList.h"
#include "../../../Include/VSSharedData/VSSharedRenderPassDataLists.h"
#include "../../../Include/VSSharedData/VSSharedPipelineDataLists.h"

#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedDataMainListInternal.h"
#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedDescriptorDataListInternal.h"
#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedRenderPassDataListsInternal.h"
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

	SharedRenderPassDataLists SharedDataMainList::GetSharedRenderPassDataLists()
	{
		return _internal.GetSharedRenderPassDataLists();
	}

	SharedPipelineDataLists SharedDataMainList::GetSharedPipelineDataLists()
	{
		return _internal.GetPipelineDataLists();
	}

	const SharedDescriptorDataList SharedDataMainList::GetSharedDescriptorDataList() const
	{
		return _internal.GetSharedDescriptorDataList();
	}

	const SharedRenderPassDataLists SharedDataMainList::GetSharedRenderPassDataLists() const
	{
		return _internal.GetSharedRenderPassDataLists();
	}

	const SharedPipelineDataLists SharedDataMainList::GetSharedPipelineDataLists() const
	{
		return _internal.GetPipelineDataLists();
	}

}