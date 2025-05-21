#include "pch.h"
#include "CreateDescriptorData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanPipelineData.h"
#include "VulkanMemoryData.h"
#include "VulkanDescriptorData.h"

#include "SwapchainSizes.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSDescriptorDataLists.h>

#include <VSDescriptorTypeFlags.h>
#include <VSUniformBufferDescriptorSetWriteData.h>

void CreateDescriptorData(VulkanData& data)
{
	data.descriptorData = std::make_unique<VulkanDescriptorData>();

	auto descriptorDataList = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass().GetDescriptorDataLists();

	data.descriptorData->descriptorPool = descriptorDataList.AddNoIndividualFreeingDescriptorPool(framesInFlight,
		{ {VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER, framesInFlight} });

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorLayouts;
	descriptorLayouts.resize(framesInFlight, data.pipelineData->descriptorLayout);

	data.descriptorData->uniformDescriptorSets = descriptorDataList.AllocateNIFUniformBufferDescriptorSets(data.descriptorData->descriptorPool,
		descriptorLayouts);

	std::vector<VulkanSimplified::UniformBufferDescriptorSetWriteData> writeData;
	writeData.resize(framesInFlight);

	for (uint32_t i = 0; i < framesInFlight; ++i)
	{
		writeData[i].descriptorSetID = data.descriptorData->uniformDescriptorSets[i];
		writeData[i].binding = 0;
		writeData[i].startArrayIndex = 0;
		writeData[i].uniformBufferIDList.push_back(data.memoryData->uniformBuffers[i]);
	}

	descriptorDataList.WriteNIFUniformBufferDescriptorSets(data.descriptorData->descriptorPool, writeData);
}
