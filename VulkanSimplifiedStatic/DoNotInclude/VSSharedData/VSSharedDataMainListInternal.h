#pragma once

#include "VSSharedDescriptorDataListInternal.h"
#include "VSSharedRenderPassDataInternal.h"
#include "VSSharedPipelineDataListInternal.h"

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

		SharedDescriptorDataListInternal& GetDescriptorDataList();
		SharedRenderPassDataListInternal& GetRenderPassDataList();
		SharedPipelineDataListInternal& GetPipelineDataList();

		const SharedDescriptorDataListInternal& GetDescriptorDataList() const;
		const SharedRenderPassDataListInternal& GetRenderPassDataList() const;
		const SharedPipelineDataListInternal& GetPipelineDataList() const;

	private:
		SharedDescriptorDataListInternal _descriptorData;
		SharedRenderPassDataListInternal _renderPassData;
		SharedPipelineDataListInternal _pipelineData;
	};
}