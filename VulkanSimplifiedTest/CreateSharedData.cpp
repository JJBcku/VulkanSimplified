#include "pch.h"
#include "CreateSharedData.h"

#include "SwapchainSizes.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
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

void CreateSharedData(VulkanData& data)
{
	data.sharedData = std::make_unique<VulkanSharedData>();
	auto& sharedDataList = *data.sharedData;

	auto sharedData = data.basicData->vsmain->GetSharedDataMainList();
	auto pipelineData = sharedData.GetSharedPipelineDataListss();
	auto descriptorData = sharedData.GetSharedDescriptorDataList();

	sharedDataList.fragmentShaderData = pipelineData.AddSharedShaderPipelineData("main", VulkanSimplified::SHADER_TYPE_FRAGMENT);
	sharedDataList.vertexShaderData = pipelineData.AddSharedShaderPipelineData("main", VulkanSimplified::SHADER_TYPE_VERTEX);

	sharedDataList.vertexAttribute1Data = pipelineData.AddVertexAttributeDescriptionData(0, VulkanSimplified::DATA_FORMAT_RGBA32_SFLOAT, 2);
	sharedDataList.vertexAttribute2Data = pipelineData.AddVertexAttributeDescriptionData(sizeof(glm::vec4), VulkanSimplified::DATA_FORMAT_RG32_SFLOAT, 2);
	sharedDataList.vertexBindingData = pipelineData.AddVertexBindingData(sizeof(VertexData), VulkanSimplified::VertexBindingInputRate::VERTEX,
		{ sharedDataList.vertexAttribute1Data, sharedDataList.vertexAttribute2Data });

	sharedDataList.vertexInputData = pipelineData.AddVertexInputSharedPipelineData({ sharedDataList.vertexBindingData });

	sharedDataList.scissorData = pipelineData.AddPipelineScissorData(0, 0, width, height);
	sharedDataList.viewportData = pipelineData.AddPipelineViewportData(0, 0, width, height, 0.0f, 1.0f);

	sharedDataList.inputAssemblyData = pipelineData.AddPipelineInputAssemblyData(VulkanSimplified::PipelinePrimitiveTopology::TRIANGLE_LIST, false);
	sharedDataList.rasterizationData = pipelineData.AddPipelineRasterizationData(VulkanSimplified::PipelinePolygonMode::FILL, true, false);
	sharedDataList.multisamplingData = pipelineData.AddPipelineMultisampleData(VulkanSimplified::SAMPLE_1, {});

	VulkanSimplified::ColorBlendingComponentFlags colorBlendingComponents = VulkanSimplified::COLOR_COMPONENT_R | VulkanSimplified::COLOR_COMPONENT_G |
		VulkanSimplified::COLOR_COMPONENT_B | VulkanSimplified::COLOR_COMPONENT_A;

	sharedDataList.colorBlendData = pipelineData.AddPipelineColorBlendAttachment(colorBlendingComponents, VulkanSimplified::ColorBlendingPreset::NO_BLENDING);

	sharedDataList.uniformBufferBinding = descriptorData.AddDescriptorSetLayoutBindingsData(VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER, 1,
		VulkanSimplified::SHADER_TYPE_VERTEX);

	sharedDataList.textureBinding = descriptorData.AddDescriptorSetLayoutBindingsData(VulkanSimplified::DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER, 1,
		VulkanSimplified::SHADER_TYPE_FRAGMENT);
}
