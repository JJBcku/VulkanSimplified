#include "pch.h"
#include "CreatePipelineData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanDeviceDependentData.h"
#include "VulkanRenderPassData.h"
#include "VulkanSharedData.h"
#include "VulkanPipelineData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSPipelineDataLists.h>
#include <VSDescriptorDataLists.h>

#include <VSSharedDataMainList.h>
#include <VSSharedPipelineDataLists.h>

#include <VSPipelineLayoutCreationData.h>
#include <VSGraphicsPipelineCreationData.h>

void CreatePipelineData(VulkanData& data)
{
	auto instance = data.basicData->vsmain->GetInstance();
	auto deviceMain = instance.GetChoosenDevicesMainClass();
	auto devicePipelineDataList = deviceMain.GetPipelineDataLists();
	auto descriptorDataList = deviceMain.GetDescriptorDataLists();

	data.pipelineData = std::make_unique<VulkanPipelineData>();

	data.pipelineData->descriptorLayout = descriptorDataList.AddDescriptorSetLayout(0, { { data.sharedData->uniformBufferBinding, {}},
		{data.sharedData->textureBinding, {data.deviceDependentData->sampler}} });

	VulkanSimplified::PipelineLayoutCreationData layoutData;
	layoutData._descriptorSets = { data.pipelineData->descriptorLayout };

	data.pipelineData->pipelineLayout = devicePipelineDataList.AddPipelineLayout(layoutData);

	{
		VulkanSimplified::GraphicsPipelineCreationData pipelineData;

		pipelineData.shaderStages.reserve(2);
		VulkanSimplified::ShaderStageData stageData;

		stageData.sharedData = data.sharedData->fragmentShaderData;
		stageData.shaderDeviceID.type = VulkanSimplified::SHADER_TYPE_FRAGMENT;
		stageData.shaderDeviceID.fragmentShader.fragmentShaderID = data.deviceDependentData->fragmentShadersID;
		pipelineData.shaderStages.push_back(stageData);

		stageData.sharedData = data.sharedData->vertexShaderData;
		stageData.shaderDeviceID.type = VulkanSimplified::SHADER_TYPE_VERTEX;
		stageData.shaderDeviceID.vertexShader.vertexShaderID = data.deviceDependentData->vertexShadersID;
		pipelineData.shaderStages.push_back(stageData);

		pipelineData.vertexInputData = data.sharedData->vertexInputData;
		pipelineData.inputAssemblyData = data.sharedData->inputAssemblyData;

		VulkanSimplified::ViewportStatePipelineDataPoint viewportData;
		viewportData.viewport = data.sharedData->viewportData;
		viewportData.scissor = data.sharedData->scissorData;
		pipelineData.viewportData.push_back(viewportData);

		pipelineData.rasterizationData = data.sharedData->rasterizationData;
		pipelineData.samplingData = data.sharedData->multisamplingData;
		pipelineData.colorBlendingData.push_back(data.sharedData->colorBlendData);

		pipelineData.pipelineLayout = data.pipelineData->pipelineLayout;
		pipelineData.renderPass = data.renderPassData->renderPass;
		pipelineData.subpassIndex = 0;
		pipelineData.pipelineDerrivationData.settings = VulkanSimplified::PipelineDerrivationSettings::DO_NOT_DERRIVE;

		auto pipelineIDs = devicePipelineDataList.AddGraphicPipelines({ pipelineData });
		data.pipelineData->pipeline = pipelineIDs[0];
	}
}
