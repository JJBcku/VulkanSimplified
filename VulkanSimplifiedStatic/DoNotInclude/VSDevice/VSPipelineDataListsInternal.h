#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include <vector>

typedef struct VkDevice_T* VkDevice;
typedef struct VkPipelineLayout_T* VkPipelineLayout;
typedef struct VkPipeline_T* VkPipeline;

namespace VulkanSimplified
{
	struct PipelineDataListsInitialCapacities;
	struct PipelineLayoutCreationData;
	struct GraphicsPipelineCreationData;
}

namespace VulkanSimplifiedInternal
{
	class SharedPipelineDataListInternal;
	class DescriptorDataListsInternal;
	class ShaderListsInternal;
	class RenderPassListInternal;

	class AutoCleanupPipelineLayout;
	class AutoCleanupGraphicsPipeline;

	class PipelineDataListsInternal
	{
	public:
		PipelineDataListsInternal(const SharedPipelineDataListInternal& pipelineData, const DescriptorDataListsInternal& descriptorData, const ShaderListsInternal& shaderList,
			const RenderPassListInternal& renderPassList, VkDevice device, const VulkanSimplified::PipelineDataListsInitialCapacities& initialCapacities);
		~PipelineDataListsInternal();

		IDObject<AutoCleanupPipelineLayout> AddPipelineLayout(const VulkanSimplified::PipelineLayoutCreationData& creationData, size_t addOnReserving);
		std::vector<IDObject<AutoCleanupGraphicsPipeline>> AddGraphicPipelines(const std::vector<VulkanSimplified::GraphicsPipelineCreationData>& creationDataList,
			size_t addOnReserving);

		VkPipelineLayout GetPipelineLayout(IDObject<AutoCleanupPipelineLayout> layoutID) const;
		VkPipeline GetGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID) const;

	private:
		const SharedPipelineDataListInternal& _pipelineData;
		const DescriptorDataListsInternal& _descriptorData;
		const ShaderListsInternal& _shaderList;
		const RenderPassListInternal& _renderPassList;

		VkDevice _device;

		UnsortedIDVector<AutoCleanupPipelineLayout> _pipelineLayoutList;
		UnsortedIDVector<AutoCleanupGraphicsPipeline> _graphicPipelineList;
	};
}