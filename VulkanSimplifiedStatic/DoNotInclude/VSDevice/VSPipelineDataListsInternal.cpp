#include "VSDeviceNIpch.h"
#include "VSPipelineDataListsInternal.h"

#include "VSAutoCleanupPipelineLayout.h"
#include "VSAutoCleanupGraphicsPipeline.h"

#include "../../Include/VSDevice/VSPipelineDataListsInitialCapacities.h"
#include "../../Include/VSDevice/VSPipelineLayoutCreationData.h"

#include "../VSSharedData/VSSharedPipelineDataListInternal.h"

#include "VSDescriptorDataListInternal.h"
#include "VSShaderListsInternal.h"
#include "VSRenderPassDataListInternal.h"

namespace VulkanSimplifiedInternal
{
    PipelineDataListsInternal::PipelineDataListsInternal(const SharedPipelineDataListInternal& pipelineData, const DescriptorDataListInternal& descriptorData,
        const ShaderListsInternal& shaderList,  const RenderPassListInternal& renderPassList, VkDevice device,
        const VulkanSimplified::PipelineDataListsInitialCapacities& initialCapacities) : _pipelineData(pipelineData), _descriptorData(descriptorData), _shaderList(shaderList),
        _renderPassList(renderPassList), _device(device), _pipelineLayoutList(initialCapacities.pipelineLayoutListInitialCapacity),
        _graphicPipelineList(initialCapacities.graphicsPipelineListInitialCapacity)
    {
    }

    PipelineDataListsInternal::~PipelineDataListsInternal()
    {
    }

    IDObject<AutoCleanupPipelineLayout> PipelineDataListsInternal::AddPipelineLayout(const VulkanSimplified::PipelineLayoutCreationData& creationData, size_t addOnReserving)
    {
		VkPipelineLayout add = VK_NULL_HANDLE;
		VkPipelineLayoutCreateInfo createInfo{};

		auto descriptorLayouts = _descriptorData.GetDescriptorSetLayouts(creationData._descriptorSets);
		auto pushConstants = _pipelineData.GetPushConstantData(creationData._pushConstants);

		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

		if (!descriptorLayouts.empty())
		{
			createInfo.setLayoutCount = static_cast<std::uint32_t>(descriptorLayouts.size());
			createInfo.pSetLayouts = descriptorLayouts.data();
		}

		if (!pushConstants.empty())
		{
			createInfo.pushConstantRangeCount = static_cast<std::uint32_t>(pushConstants.size());
			createInfo.pPushConstantRanges = pushConstants.data();
		}

		if (vkCreatePipelineLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("PipelineDataListsInternal::AddPipelineLayout Error: Program failed to create the pipeline layout!");

		return _pipelineLayoutList.AddObject(AutoCleanupPipelineLayout(_device, add), addOnReserving);
    }

}