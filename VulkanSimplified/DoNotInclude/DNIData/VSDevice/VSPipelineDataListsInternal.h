#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include <vector>
#include <optional>

#include <vulkan/vulkan.hpp>

#include "../../../Include/VSDevice/VSPipelineDataListsDef.h"

typedef struct VkDevice_T* VkDevice;
typedef struct VkPipelineLayout_T* VkPipelineLayout;
typedef struct VkPipeline_T* VkPipeline;

namespace VulkanSimplified
{
	struct PipelineDataListsInitialCapacities;
	struct PipelineLayoutCreationData;
	struct GraphicsPipelineCreationData;
}

namespace VulkanSimplified
{
	class SharedPipelineDataListsInternal;
	class DescriptorDataListsInternal;
	class ShaderListsInternal;
	class RenderPassListInternal;

	class PipelineDataListsInternal
	{
	public:
		PipelineDataListsInternal(const SharedPipelineDataListsInternal& pipelineData, const DescriptorDataListsInternal& descriptorData, const ShaderListsInternal& shaderList,
			const RenderPassListInternal& renderPassList, VkDevice device, const PipelineDataListsInitialCapacities& initialCapacities);
		~PipelineDataListsInternal();

		std::optional<IDObject<AutoCleanupPipelineCache>> AddPipelineCache(const std::vector<unsigned char>& initialData, size_t addOnReserving);

		IDObject<AutoCleanupPipelineLayout> AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving);
		std::vector<IDObject<AutoCleanupGraphicsPipeline>> AddGraphicPipelines(const std::vector<GraphicsPipelineCreationData>& creationDataList,
			const std::optional<IDObject<AutoCleanupPipelineCache>>& pipelineCacheID, size_t addOnReserving);

		size_t GetPipelineCacheSize(IDObject<AutoCleanupPipelineCache> cacheID) const;
		std::vector<unsigned char> GetPipelineCacheData(IDObject<AutoCleanupPipelineCache> cacheID) const;

		VkPipelineLayout GetPipelineLayout(IDObject<AutoCleanupPipelineLayout> layoutID) const;
		VkPipeline GetGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID) const;

	private:
		const SharedPipelineDataListsInternal& _pipelineData;
		const DescriptorDataListsInternal& _descriptorData;
		const ShaderListsInternal& _shaderList;
		const RenderPassListInternal& _renderPassList;

		VkDevice _device;

		VkPipelineCacheHeaderVersionOne _pipelineHeader;
		UnsortedIDVector<AutoCleanupPipelineCache> _pipelineCacheList;

		UnsortedIDVector<AutoCleanupPipelineLayout> _pipelineLayoutList;
		UnsortedIDVector<AutoCleanupGraphicsPipeline> _graphicPipelineList;
	};
}