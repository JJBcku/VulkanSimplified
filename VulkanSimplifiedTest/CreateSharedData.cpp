#include "pch.h"
#include "CreateSharedData.h"

#include "SwapchainSizes.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanSharedData.h"

#include <VSMain.h>
#include <VSSharedDataMainList.h>
#include <VSSharedPipelineDataLists.h>
#include <VSSharedDescriptorDataList.h>
#include <VSShaderTypeFlags.h>
#include <VSPipelinePrimitiveTopology.h>
#include <VSPipelinePolygonMode.h>
#include <VSImageSampleFlags.h>
#include <VSColorBlendingPreset.h>
#include <VSColorBlendingComponentFlags.h>

#include "VertexData.h"

#include <VSDataFormatFlags.h>
#include <VSVertexBindingInputRate.h>

#include <VSDescriptorTypeFlags.h>
#include <VSDepthUsage.h>
#include <VSCompareOperationsType.h>

void CreateSharedData(VulkanData& data)
{
	data.sharedData = std::make_unique<VulkanSharedData>();
	auto& sharedDataList = *data.sharedData;

	auto sharedData = data.basicData->vsmain->GetSharedDataMainList();
	auto pipelineData = sharedData.GetSharedPipelineDataLists();
	auto descriptorData = sharedData.GetSharedDescriptorDataList();

	sharedDataList.fragmentShaderData = pipelineData.AddSharedShaderPipelineData("main", VS::SHADER_TYPE_FRAGMENT);
	sharedDataList.vertexShaderData = pipelineData.AddSharedShaderPipelineData("main", VS::SHADER_TYPE_VERTEX);

	sharedDataList.vertexAttribute1Data = pipelineData.AddVertexAttributeDescriptionData(0, VS::DATA_FORMAT_RGBA32_SFLOAT, 2);
	sharedDataList.vertexAttribute2Data = pipelineData.AddVertexAttributeDescriptionData(sizeof(glm::vec4), VS::DATA_FORMAT_RG32_SFLOAT, 2);
	sharedDataList.vertexBindingData = pipelineData.AddVertexBindingData(sizeof(VertexData), VS::VertexBindingInputRate::VERTEX,
		{ sharedDataList.vertexAttribute1Data, sharedDataList.vertexAttribute2Data });

	sharedDataList.vertexInputData = pipelineData.AddVertexInputSharedPipelineData({ sharedDataList.vertexBindingData });

	sharedDataList.scissorData = pipelineData.AddPipelineScissorData(0, 0, swapchainWidth, swapchainHeight);
	sharedDataList.viewportData = pipelineData.AddPipelineViewportData(0, 0, swapchainWidth, swapchainHeight, 0.0f, 1.0f);

	sharedDataList.inputAssemblyData = pipelineData.AddPipelineInputAssemblyData(VS::PipelinePrimitiveTopology::TRIANGLE_LIST, false);
	sharedDataList.rasterizationData = pipelineData.AddPipelineRasterizationData(VS::PipelinePolygonMode::FILL, false, false);
	sharedDataList.multisamplingData = pipelineData.AddPipelineMultisampleData(data.instanceDependentData->maxSamples, data.instanceDependentData->sampleShadingRate);

	sharedDataList.depthStencilData = pipelineData.AddPipelineDepthStencilStateData(VS::DepthUsage::TEST_AND_WRITE,
		VS::CompareOperationsType::COMPARE_OPERATION_LESS, 0.0f, 1.0f);

	VS::ColorBlendingComponentFlags colorBlendingComponents = VS::COLOR_COMPONENT_R | VS::COLOR_COMPONENT_G |
		VS::COLOR_COMPONENT_B | VS::COLOR_COMPONENT_A;

	sharedDataList.colorBlendData = pipelineData.AddPipelineColorBlendAttachment(colorBlendingComponents, VS::ColorBlendingPreset::NO_BLENDING);

	sharedDataList.uniformBufferBinding = descriptorData.AddDescriptorSetLayoutBindingsData(VS::DescriptorTypeFlagBits::UNIFORM_BUFFER, 1,
		VS::SHADER_TYPE_VERTEX);

	sharedDataList.textureBinding = descriptorData.AddDescriptorSetLayoutBindingsData(VS::DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER, 1,
		VS::SHADER_TYPE_FRAGMENT);
}
