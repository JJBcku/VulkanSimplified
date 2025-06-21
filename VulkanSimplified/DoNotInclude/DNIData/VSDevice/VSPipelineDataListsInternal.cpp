#include "VSDeviceNIpch.h"
#include "VSPipelineDataListsInternal.h"

#include "VSAutoCleanupPipelineLayout.h"
#include "VSAutoCleanupGraphicsPipeline.h"

#include "../../../Include/VSDevice/VSPipelineDataListsInitialCapacities.h"
#include "../../../Include/VSDevice/VSPipelineLayoutCreationData.h"
#include "../../../Include/VSDevice/VSGraphicsPipelineCreationData.h"

#include "../VSSharedData/VSSharedPipelineDataListsInternal.h"

#include "VSDescriptorDataListsInternal.h"
#include "VSShaderListsInternal.h"
#include "VSRenderPassDataListInternal.h"

namespace VulkanSimplified
{
    PipelineDataListsInternal::PipelineDataListsInternal(const SharedPipelineDataListInternal& pipelineData, const DescriptorDataListsInternal& descriptorData,
        const ShaderListsInternal& shaderList,  const RenderPassListInternal& renderPassList, VkDevice device,
        const PipelineDataListsInitialCapacities& initialCapacities) : _pipelineData(pipelineData), _descriptorData(descriptorData), _shaderList(shaderList),
        _renderPassList(renderPassList), _device(device), _pipelineLayoutList(initialCapacities.pipelineLayoutListInitialCapacity),
        _graphicPipelineList(initialCapacities.graphicsPipelineListInitialCapacity)
    {
    }

    PipelineDataListsInternal::~PipelineDataListsInternal()
    {
    }

    IDObject<AutoCleanupPipelineLayout> PipelineDataListsInternal::AddPipelineLayout(const PipelineLayoutCreationData& creationData, size_t addOnReserving)
    {
		VkPipelineLayout add = VK_NULL_HANDLE;
		VkPipelineLayoutCreateInfo createInfo{};

		auto descriptorLayouts = _descriptorData.GetDescriptorSetLayouts(creationData._descriptorSets);
		auto pushConstants = _pipelineData.GetPushConstantData(creationData._pushConstants);

		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

		if (!descriptorLayouts.empty())
		{
			createInfo.setLayoutCount = static_cast<uint32_t>(descriptorLayouts.size());
			createInfo.pSetLayouts = descriptorLayouts.data();
		}

		if (!pushConstants.empty())
		{
			createInfo.pushConstantRangeCount = static_cast<uint32_t>(pushConstants.size());
			createInfo.pPushConstantRanges = pushConstants.data();
		}

		if (vkCreatePipelineLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("PipelineDataListsInternal::AddPipelineLayout Error: Program failed to create the pipeline layout!");

		return _pipelineLayoutList.AddObject(AutoCleanupPipelineLayout(_device, add), addOnReserving);
    }

	std::vector<IDObject<AutoCleanupGraphicsPipeline>> PipelineDataListsInternal::AddGraphicPipelines(const std::vector<GraphicsPipelineCreationData>& creationDataList,
		size_t addOnReserving)
	{
		assert(!creationDataList.empty());

		std::vector<IDObject<AutoCleanupGraphicsPipeline>> ret;
		ret.reserve(creationDataList.size());

		std::vector<VkGraphicsPipelineCreateInfo> createInfoList;

		std::vector<std::vector<VkPipelineShaderStageCreateInfo>> shaderStageList;
		std::vector<std::vector<std::string>> shaderStageNameList;
		std::vector<std::vector<VkSpecializationInfo>> shaderSpecializationInfoList;
		std::vector<std::vector<std::vector<VkSpecializationMapEntry>>> specializationData;

		std::vector<VkPipelineVertexInputStateCreateInfo> vertexInputList;
		std::vector<std::vector<VkVertexInputBindingDescription>> vertexInputBindingList;
		std::vector<std::vector<VkVertexInputAttributeDescription>> vertexInputAttributeList;

		std::vector<VkPipelineInputAssemblyStateCreateInfo> vertexInputAssemblyList;

		std::vector<VkPipelineViewportStateCreateInfo> viewportStateList;
		std::vector<std::vector<VkViewport>> viewportList;
		std::vector<std::vector<VkRect2D>> scissorList;

		std::vector<VkPipelineRasterizationStateCreateInfo> rasterizationStateList;
		std::vector<VkPipelineMultisampleStateCreateInfo> multisamplingStateList;
		std::vector<VkPipelineDepthStencilStateCreateInfo> depthStencilStateList;

		std::vector<VkPipelineColorBlendStateCreateInfo> colorBlendStateList;
		std::vector<std::vector<VkPipelineColorBlendAttachmentState>> colorBlendAttachmentStateList;

		createInfoList.reserve(creationDataList.size());

		shaderStageList.resize(creationDataList.size());
		shaderStageNameList.resize(creationDataList.size());
		shaderSpecializationInfoList.resize(creationDataList.size());
		specializationData.resize(creationDataList.size());

		vertexInputList.reserve(creationDataList.size());
		vertexInputBindingList.resize(creationDataList.size());
		vertexInputAttributeList.resize(creationDataList.size());

		vertexInputAssemblyList.reserve(creationDataList.size());

		viewportStateList.reserve(creationDataList.size());
		viewportList.resize(creationDataList.size());
		scissorList.resize(creationDataList.size());

		rasterizationStateList.reserve(creationDataList.size());
		multisamplingStateList.reserve(creationDataList.size());
		depthStencilStateList.reserve(creationDataList.size());

		colorBlendStateList.reserve(creationDataList.size());
		colorBlendAttachmentStateList.resize(creationDataList.size());

		for (size_t i = 0; i < creationDataList.size(); i++)
		{
			VkGraphicsPipelineCreateInfo pipelineAdd{};
			pipelineAdd.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

			pipelineAdd.flags = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
			pipelineAdd.flags |= VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;
#endif

			if (!creationDataList[i].shaderStages.empty())
			{
				shaderStageList[i].reserve(creationDataList[i].shaderStages.size());
				shaderStageNameList[i].reserve(creationDataList[i].shaderStages.size());
				shaderSpecializationInfoList[i].resize(creationDataList[i].shaderStages.size());
				specializationData[i].resize(creationDataList[i].shaderStages.size());

				for (size_t j = 0; j < creationDataList[i].shaderStages.size(); j++)
				{
					VkPipelineShaderStageCreateInfo shaderInfo{};
					shaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

					auto shaderData = _pipelineData.GetSharedShaderPipelineData(creationDataList[i].shaderStages[j].sharedData);

					shaderInfo.stage = shaderData.shaderStage;
					shaderInfo.module = _shaderList.GetShaderModule(creationDataList[i].shaderStages[j].shaderDeviceID);

					shaderStageNameList[i].push_back(shaderData.entryPointName);
					shaderInfo.pName = shaderStageNameList[i].back().c_str();

					if (creationDataList[i].shaderStages[j].specializationData.has_value() && !creationDataList[i].shaderStages[j].specializationData->specializationElements.empty())
					{
						specializationData[i][j] = _pipelineData.GetShaderSpecializationData(creationDataList[i].shaderStages[j].specializationData->specializationElements);

						shaderSpecializationInfoList[i][j].mapEntryCount = static_cast<uint32_t>(specializationData[i][j].size());
						shaderSpecializationInfoList[i][j].pMapEntries = specializationData[i][j].data();
						shaderSpecializationInfoList[i][j].dataSize = creationDataList[i].shaderStages[j].specializationData->dataSize;
						shaderSpecializationInfoList[i][j].pData = creationDataList[i].shaderStages[j].specializationData->data;

						shaderInfo.pSpecializationInfo = &shaderSpecializationInfoList[i][j];
					}

					shaderStageList[i].push_back(shaderInfo);
				}

				pipelineAdd.stageCount = static_cast<uint32_t>(shaderStageList[i].size());
				pipelineAdd.pStages = shaderStageList[i].data();
			}

			{
				VkPipelineVertexInputStateCreateInfo vertexAdd{};
				vertexAdd.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

				auto vertexData = _pipelineData.GetVertexInputSharedPipelineData(creationDataList[i].vertexInputData);

				if (!vertexData.vertexBindings.empty())
				{
					vertexInputBindingList[i].reserve(vertexData.vertexBindings.size());

					const auto bindingsData = _pipelineData.GetVertexBindingDescriptionData(vertexData.vertexBindings);

					size_t attributesTotalAmount = 0;

					for (auto& bindingData : bindingsData)
					{
						attributesTotalAmount += bindingData.vertexAttributes.size();
					}

					if (attributesTotalAmount > 0)
					{
						vertexInputAttributeList[i].reserve(attributesTotalAmount);
					}

					for (size_t j = 0; j < bindingsData.size(); j++)
					{
						VkVertexInputBindingDescription bindingAdd{};
						bindingAdd.binding = static_cast<uint32_t>(i);
						bindingAdd.inputRate = bindingsData[j].inputRate;
						bindingAdd.stride = bindingsData[j].stride;

						vertexInputBindingList[i].push_back(bindingAdd);

						if (!bindingsData[j].vertexAttributes.empty())
						{
							auto attributeData = _pipelineData.GetVertexAttributeDescriptionData(bindingsData[j].vertexAttributes);

							for (size_t k = 0; k < attributeData.size(); k++)
							{
								VkVertexInputAttributeDescription vertexAttributeAdd{};
								vertexAttributeAdd.location = static_cast<uint32_t>(k);
								vertexAttributeAdd.binding = bindingAdd.binding;
								vertexAttributeAdd.format = attributeData[k].format;
								vertexAttributeAdd.offset = attributeData[k].offset;

								vertexInputAttributeList[i].push_back(vertexAttributeAdd);
							}
						}
					}

					vertexAdd.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindingList[i].size());
					vertexAdd.pVertexBindingDescriptions = vertexInputBindingList[i].data();

					if (!vertexInputAttributeList[i].empty())
					{
						vertexAdd.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeList[i].size());
						vertexAdd.pVertexAttributeDescriptions = vertexInputAttributeList[i].data();
					}
				}

				vertexInputList.push_back(vertexAdd);
				pipelineAdd.pVertexInputState = &vertexInputList.back();
			}

			vertexInputAssemblyList.push_back(_pipelineData.GetInputAssembly(creationDataList[i].inputAssemblyData));
			pipelineAdd.pInputAssemblyState = &vertexInputAssemblyList.back();

			if (!creationDataList[i].viewportData.empty())
			{
				VkPipelineViewportStateCreateInfo viewportStateInfo{};
				viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

				viewportList[i].reserve(creationDataList[i].viewportData.size());
				scissorList[i].reserve(creationDataList[i].viewportData.size());

				for (size_t j = 0; j < creationDataList[i].viewportData.size(); j++)
				{
					viewportList[i].push_back(_pipelineData.GetViewports(creationDataList[i].viewportData[j].viewport));
					scissorList[i].push_back(_pipelineData.GetScissors(creationDataList[i].viewportData[j].scissor));
				}

				viewportStateInfo.viewportCount = static_cast<uint32_t>(creationDataList[i].viewportData.size());
				viewportStateInfo.pViewports = viewportList[i].data();
				viewportStateInfo.scissorCount = viewportStateInfo.viewportCount;
				viewportStateInfo.pScissors = scissorList[i].data();

				viewportStateList.push_back(viewportStateInfo);
				pipelineAdd.pViewportState = &viewportStateList.back();
			}

			rasterizationStateList.push_back(_pipelineData.GetRasterizationState(creationDataList[i].rasterizationData));
			pipelineAdd.pRasterizationState = &rasterizationStateList.back();

			multisamplingStateList.push_back(_pipelineData.GetMultisamplingState(creationDataList[i].samplingData));
			pipelineAdd.pMultisampleState = &multisamplingStateList.back();

			if (creationDataList[i].depthStencilData.has_value())
			{
				depthStencilStateList.push_back(_pipelineData.GetDepthStencilState(creationDataList[i].depthStencilData.value()));
				pipelineAdd.pDepthStencilState = &depthStencilStateList.back();
			}

			if (!creationDataList[i].colorBlendingData.empty())
			{
				colorBlendAttachmentStateList[i] = _pipelineData.GetColorBlendAttachments(creationDataList[i].colorBlendingData);

				VkPipelineColorBlendStateCreateInfo colorBlendAdd{};
				colorBlendAdd.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				colorBlendAdd.logicOpEnable = VK_FALSE;
				colorBlendAdd.attachmentCount = static_cast<uint32_t>(colorBlendAttachmentStateList[i].size());
				colorBlendAdd.pAttachments = colorBlendAttachmentStateList[i].data();
				colorBlendAdd.blendConstants[0] = 1.0f;
				colorBlendAdd.blendConstants[1] = 1.0f;
				colorBlendAdd.blendConstants[2] = 1.0f;
				colorBlendAdd.blendConstants[3] = 1.0f;

				colorBlendStateList.push_back(colorBlendAdd);
				pipelineAdd.pColorBlendState = &colorBlendStateList.back();
			}

			pipelineAdd.layout = GetPipelineLayout(creationDataList[i].pipelineLayout);
			pipelineAdd.renderPass = _renderPassList.GetRenderPass(creationDataList[i].renderPass);
			pipelineAdd.subpass = creationDataList[i].subpassIndex;

			switch (creationDataList[i].pipelineDerrivationData.settings)
			{
			case PipelineDerrivationSettings::DO_NOT_DERRIVE:
				pipelineAdd.basePipelineHandle = VK_NULL_HANDLE;
				pipelineAdd.basePipelineIndex = -1;
				break;
			case PipelineDerrivationSettings::PIPELINE_ID:
				pipelineAdd.basePipelineHandle = GetGraphicsPipeline(creationDataList[i].pipelineDerrivationData.pipelineID.ID);
				pipelineAdd.basePipelineIndex = -1;
				break;
			case PipelineDerrivationSettings::PIPELINE_INDEX:
				pipelineAdd.basePipelineHandle = VK_NULL_HANDLE;
				pipelineAdd.basePipelineIndex = static_cast<int32_t>(creationDataList[i].pipelineDerrivationData.pipelineIndex.index);
				pipelineAdd.flags |= VK_PIPELINE_CREATE_DERIVATIVE_BIT;
				break;
			default:
				throw std::runtime_error("DevicePipelineDataInternal::AddGraphicPipelines Error: Program was given an erroneous pipeline derrivation setting value!");
			}

			createInfoList.push_back(pipelineAdd);
		}

		std::vector<VkPipeline> pipelineList;
		pipelineList.resize(creationDataList.size(), VK_NULL_HANDLE);

		if (vkCreateGraphicsPipelines(_device, VK_NULL_HANDLE, static_cast<uint32_t>(createInfoList.size()), createInfoList.data(), nullptr, pipelineList.data()) != VK_SUCCESS)
			throw std::runtime_error("DevicePipelineDataInternal::AddGraphicPipelines Error: Program failed to create the pipelines!");

		for (auto& pipeline : pipelineList)
		{
			ret.push_back(_graphicPipelineList.AddObject(AutoCleanupGraphicsPipeline(_device, pipeline), addOnReserving));
		}

		return ret;
	}

	VkPipelineLayout PipelineDataListsInternal::GetPipelineLayout(IDObject<AutoCleanupPipelineLayout> layoutID) const
	{
		return _pipelineLayoutList.GetConstObject(layoutID).GetPipelineLayout();
	}

	VkPipeline PipelineDataListsInternal::GetGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID) const
	{
		return _graphicPipelineList.GetConstObject(pipelineID).GetPipeline();
	}

}