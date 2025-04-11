#include "VSSharedNIpch.h"
#include "VSSharedDataMainListInternal.h"

#include "../../Include/VSSharedData/VSSharedDataListsCapacities.h"

namespace VulkanSimplifiedInternal
{
	SharedDataMainListInternal::SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities) :
		_descriptorData(initialCapabilities.descriptorLists), _renderPassData(initialCapabilities.renderPassLists), _pipelineData(initialCapabilities.pipelineLists)
	{
	}

	SharedDataMainListInternal::~SharedDataMainListInternal()
	{
	}

	SharedDescriptorDataListInternal& SharedDataMainListInternal::GetDescriptorDataList()
	{
		return _descriptorData;
	}

	SharedRenderPassDataListInternal& SharedDataMainListInternal::GetRenderPassDataList()
	{
		return _renderPassData;
	}

	SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList()
	{
		return _pipelineData;
	}

	const SharedDescriptorDataListInternal& SharedDataMainListInternal::GetDescriptorDataList() const
	{
		return _descriptorData;
	}

	const SharedRenderPassDataListInternal& SharedDataMainListInternal::GetRenderPassDataList() const
	{
		return _renderPassData;
	}

	const SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList() const
	{
		return _pipelineData;
	}

}