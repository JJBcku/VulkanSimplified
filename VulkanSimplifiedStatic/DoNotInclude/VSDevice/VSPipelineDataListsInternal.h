#pragma once

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplified
{
	struct PipelineDataListsInitialCapacities;
	struct PipelineLayoutCreationData;
}

namespace VulkanSimplifiedInternal
{
	class SharedPipelineDataListInternal;
	class DescriptorDataListInternal;
	class ShaderListsInternal;
	class RenderPassListInternal;

	class AutoCleanupPipelineLayout;
	class AutoCleanupGraphicsPipeline;

	class PipelineDataListsInternal
	{
	public:
		PipelineDataListsInternal(const SharedPipelineDataListInternal& pipelineData, const DescriptorDataListInternal& descriptorData, const ShaderListsInternal& shaderList,
			const RenderPassListInternal& renderPassList, VkDevice device, const VulkanSimplified::PipelineDataListsInitialCapacities& initialCapacities);
		~PipelineDataListsInternal();

		IDObject<AutoCleanupPipelineLayout> AddPipelineLayout(const VulkanSimplified::PipelineLayoutCreationData& creationData, size_t addOnReserving);

	private:
		const SharedPipelineDataListInternal& _pipelineData;
		const DescriptorDataListInternal& _descriptorData;
		const ShaderListsInternal& _shaderList;
		const RenderPassListInternal& _renderPassList;

		VkDevice _device;

		UnsortedIDVector<AutoCleanupPipelineLayout> _pipelineLayoutList;
		UnsortedIDVector<AutoCleanupGraphicsPipeline> _graphicPipelineList;
	};
}