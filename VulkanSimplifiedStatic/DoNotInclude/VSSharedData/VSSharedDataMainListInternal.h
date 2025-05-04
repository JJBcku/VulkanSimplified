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

		SharedDescriptorDataListInternal& GetDescriptorDataList();
		SharedRenderPassDataListInternal& GetRenderPassDataList();
		SharedPipelineDataListssInternal& GetPipelineDataList();

		const SharedDescriptorDataListInternal& GetDescriptorDataList() const;
		const SharedRenderPassDataListInternal& GetRenderPassDataList() const;
		const SharedPipelineDataListssInternal& GetPipelineDataList() const;

	private:
		SharedDescriptorDataListInternal _descriptorData;
		SharedRenderPassDataListInternal _renderPassData;
		SharedPipelineDataListssInternal _pipelineData;
	};
}