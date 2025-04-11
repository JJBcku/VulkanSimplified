#include "VSSharedNIpch.h"
#include "VSSharedDataMainListInternal.h"

#include "../../Include/VSSharedData/VSSharedDataListsCapacities.h"

namespace VulkanSimplifiedInternal
{
	SharedDataMainListInternal::SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities) :
		_descriptorData(initialCapabilities.descriptorLists), _pipelineData(initialCapabilities.pipelineLists)
	{
	}

	SharedDataMainListInternal::~SharedDataMainListInternal()
	{
	}

	SharedDescriptorDataListInternal& SharedDataMainListInternal::GetDescriptorDataList()
	{
		return _descriptorData;
	}

	SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList()
	{
		return _pipelineData;
	}

	const SharedDescriptorDataListInternal& SharedDataMainListInternal::GetDescriptorDataList() const
	{
		return _descriptorData;
	}

	const SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList() const
	{
		return _pipelineData;
	}

}