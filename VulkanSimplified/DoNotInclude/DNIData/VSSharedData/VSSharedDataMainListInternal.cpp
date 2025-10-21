#include "VSSharedDNIpch.h"
#include "VSSharedDataMainListInternal.h"

#include "../../../Include/VSSharedData/VSSharedDataListsCapacities.h"

#include "VSSharedDescriptorDataListInternal.h"
#include "VSSharedRenderPassDataListsInternal.h"
#include "VSSharedPipelineDataListsInternal.h"

namespace VulkanSimplified
{
	SharedDataMainListInternal::SharedDataMainListInternal(const SharedDataListsCapacities& initialCapabilities) :
		_descriptorData(std::make_unique<SharedDescriptorDataListInternal>(initialCapabilities.descriptorLists)),
		_renderPassData(std::make_unique<SharedRenderPassDataListsInternal>(initialCapabilities.renderPassLists)),
		_pipelineData(std::make_unique<SharedPipelineDataListsInternal>(initialCapabilities.pipelineLists))
	{
	}

	SharedDataMainListInternal::~SharedDataMainListInternal()
	{
	}

	SharedDescriptorDataListInternal& SharedDataMainListInternal::GetSharedDescriptorDataList()
	{
		return *_descriptorData;
	}

	SharedRenderPassDataListsInternal& SharedDataMainListInternal::GetSharedRenderPassDataLists()
	{
		return *_renderPassData;
	}

	SharedPipelineDataListsInternal& SharedDataMainListInternal::GetPipelineDataLists()
	{
		return *_pipelineData;
	}

	const SharedDescriptorDataListInternal& SharedDataMainListInternal::GetSharedDescriptorDataList() const
	{
		return *_descriptorData;
	}

	const SharedRenderPassDataListsInternal& SharedDataMainListInternal::GetSharedRenderPassDataLists() const
	{
		return *_renderPassData;
	}

	const SharedPipelineDataListsInternal& SharedDataMainListInternal::GetPipelineDataLists() const
	{
		return *_pipelineData;
	}

}