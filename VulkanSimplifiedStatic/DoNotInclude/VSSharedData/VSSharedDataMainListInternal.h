#pragma once

#include "VSSharedDescriptorDataListInternal.h"
#include "VSSharedRenderPassDataInternal.h"
#include "VSSharedPipelineDataListsInternal.h"

namespace VulkanSimplified
{
	struct SharedDataListsCapacities;
}

namespace VulkanSimplifiedInternal
{
	class SharedDataMainListInternal
	{
	public:
		SharedDataMainListInternal(const VulkanSimplified::SharedDataListsCapacities& initialCapabilities);
		~SharedDataMainListInternal();

		SharedDescriptorDataListInternal& GetSharedDescriptorDataList();
		SharedRenderPassDataListInternal& GetSharedRenderPassDataList();
		SharedPipelineDataListInternal& GetPipelineDataList();

		const SharedDescriptorDataListInternal& GetSharedDescriptorDataList() const;
		const SharedRenderPassDataListInternal& GetSharedRenderPassDataList() const;
		const SharedPipelineDataListInternal& GetPipelineDataList() const;

	private:
		SharedDescriptorDataListInternal _descriptorData;
		SharedRenderPassDataListInternal _renderPassData;
		SharedPipelineDataListInternal _pipelineData;
	};
}