#include "pch.h"
#include "CreateSharedData.h"

#include "SwapchainSizes.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanSharedData.h"

#include <VSSharedDataMainList.h>
#include <VSSharedPipelineDataLists.h>
#include <VSShaderTypeFlags.h>
#include <VSPipelinePrimitiveTopology.h>
#include <VSPipelinePolygonMode.h>
#include <VSImageSampleFlags.h>
#include <VSColorBlendingPreset.h>
#include <VSColorBlendingComponentFlags.h>

void CreateSharedData(VulkanData& data)
{
	data.sharedData = std::make_unique<VulkanSharedData>();
	auto& sharedDataList = *data.sharedData;

	auto sharedData = data.basicData->vsmain.value().GetSharedDataMainList();
	auto pipelineData = sharedData.GetSharedPipelineDataListss();

	sharedDataList.fragmentShaderData = pipelineData.AddSharedShaderPipelineData("main", VulkanSimplified::SHADER_TYPE_FRAGMENT);
	sharedDataList.vertexShaderData = pipelineData.AddSharedShaderPipelineData("main", VulkanSimplified::SHADER_TYPE_VERTEX);

	sharedDataList.vertexInputData = pipelineData.AddVertexInputSharedPipelineData({});

	sharedDataList.scissorData = pipelineData.AddPipelineScissorData(0, 0, width, height);
	sharedDataList.viewportData = pipelineData.AddPipelineViewportData(0, 0, width, height, 0.0f, 1.0f);

	sharedDataList.inputAssemblyData = pipelineData.AddPipelineInputAssemblyData(VulkanSimplified::PipelinePrimitiveTopology::TRIANGLE_LIST, false);
	sharedDataList.rasterizationData = pipelineData.AddPipelineRasterizationData(VulkanSimplified::PipelinePolygonMode::FILL, true, true);
	sharedDataList.multisamplingData = pipelineData.AddPipelineMultisampleData(VulkanSimplified::SAMPLE_1, {});

	VulkanSimplified::ColorBlendingComponentFlags colorBlendingComponents = VulkanSimplified::COLOR_COMPONENT_R | VulkanSimplified::COLOR_COMPONENT_G |
		VulkanSimplified::COLOR_COMPONENT_B | VulkanSimplified::COLOR_COMPONENT_A;

	sharedDataList.colorBlendData = pipelineData.AddPipelineColorBlendAttachment(colorBlendingComponents, VulkanSimplified::ColorBlendingPreset::NO_BLENDING);
}
