#include "pch.h"
#include "CreatePipelineData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanSharedData.h"
#include "VulkanPipelineData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSPipelineDataLists.h>

#include <VSSharedDataMainList.h>
#include <VSSharedPipelineDataList.h>

#include <VSPipelineLayoutCreationData.h>

void CreatePipelineData(VulkanData& data)
{
	auto instance = data.basicData->vsmain->GetInstance();
	auto deviceMain = instance.GetChoosenDevicesMainClass();
	auto devicePipelineDataList = deviceMain.GetPipelineDataLists();

	data.pipelineData = std::make_unique<VulkanPipelineData>();

	VulkanSimplified::PipelineLayoutCreationData layoutData;

	data.pipelineData->pipelineLayout = devicePipelineDataList.AddPipelineLayout(layoutData);
}
