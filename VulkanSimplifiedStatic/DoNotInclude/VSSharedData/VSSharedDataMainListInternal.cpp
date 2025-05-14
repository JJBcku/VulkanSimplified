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

	SharedDescriptorDataListInternal& SharedDataMainListInternal::GetSharedDescriptorDataList()
	{
		return _descriptorData;
	}

	SharedRenderPassDataListInternal& SharedDataMainListInternal::GetSharedRenderPassDataList()
	{
		return _renderPassData;
	}

	SharedPipelineDataListssInternal& SharedDataMainListInternal::GetPipelineDataList()
	{
		return _pipelineData;
	}

	const SharedDescriptorDataListInternal& SharedDataMainListInternal::GetSharedDescriptorDataList() const
	{
		return _descriptorData;
	}

	const SharedRenderPassDataListInternal& SharedDataMainListInternal::GetSharedRenderPassDataList() const
	{
		return _renderPassData;
	}

	const SharedPipelineDataListssInternal& SharedDataMainListInternal::GetPipelineDataList() const
	{
		return _pipelineData;
	}

}