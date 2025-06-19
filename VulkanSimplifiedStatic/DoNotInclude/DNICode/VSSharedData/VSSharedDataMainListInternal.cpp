#include "VSSharedNIpch.h"
#include "../../DNIHeaders/VSSharedData/VSSharedDataMainListInternal.h"

#include "../../../Include/VSSharedData/VSSharedDataListsCapacities.h"

#include "../../DNIHeaders/VSSharedData/VSSharedDescriptorDataListInternal.h"
#include "../../DNIHeaders/VSSharedData/VSSharedRenderPassDataInternal.h"
#include "../../DNIHeaders/VSSharedData/VSSharedPipelineDataListsInternal.h"

namespace VulkanSimplifiedInternal
{
	SharedDataMainListInternal::SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities) :
		_descriptorData(std::make_unique<SharedDescriptorDataListInternal>(initialCapabilities.descriptorLists)),
		_renderPassData(std::make_unique<SharedRenderPassDataListInternal>(initialCapabilities.renderPassLists)),
		_pipelineData(std::make_unique<SharedPipelineDataListInternal>(initialCapabilities.pipelineLists))
	{
	}

	SharedDataMainListInternal::~SharedDataMainListInternal()
	{
	}

	SharedDescriptorDataListInternal& SharedDataMainListInternal::GetSharedDescriptorDataList()
	{
		return *_descriptorData;
	}

	SharedRenderPassDataListInternal& SharedDataMainListInternal::GetSharedRenderPassDataList()
	{
		return *_renderPassData;
	}

	SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList()
	{
		return *_pipelineData;
	}

	const SharedDescriptorDataListInternal& SharedDataMainListInternal::GetSharedDescriptorDataList() const
	{
		return *_descriptorData;
	}

	const SharedRenderPassDataListInternal& SharedDataMainListInternal::GetSharedRenderPassDataList() const
	{
		return *_renderPassData;
	}

	const SharedPipelineDataListInternal& SharedDataMainListInternal::GetPipelineDataList() const
	{
		return *_pipelineData;
	}

}