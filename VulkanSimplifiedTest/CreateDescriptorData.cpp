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
#include <VSDescriptorSetUniformBufferBindingWriteData.h>

void CreateDescriptorData(VulkanData& data)
{
	data.descriptorData = std::make_unique<VulkanDescriptorData>();

	auto descriptorDataList = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass().GetDescriptorDataLists();

	data.descriptorData->descriptorPool = descriptorDataList.AddNoIndividualFreeingDescriptorPool(framesInFlight,
		{ {VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER, framesInFlight}, {VulkanSimplified::DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER, framesInFlight} });

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorLayouts;
	descriptorLayouts.resize(framesInFlight, data.pipelineData->descriptorLayout);

	data.descriptorData->descriptorSets = descriptorDataList.AllocateNIFDescriptorSets(data.descriptorData->descriptorPool,
		descriptorLayouts);

	std::vector<VulkanSimplified::DescriptorSetUniformBufferBindingWriteData> uniformBufferWriteData;
	uniformBufferWriteData.resize(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		uniformBufferWriteData[i].descriptorSetID = data.descriptorData->descriptorSets[i];
		uniformBufferWriteData[i].binding = 0;
		uniformBufferWriteData[i].startArrayIndex = 0;
		uniformBufferWriteData[i].uniformBufferIDList.push_back(data.memoryData->uniformBuffers[i]);
	}

	descriptorDataList.WriteNIFDescriptorSetUniformBufferBindings(data.descriptorData->descriptorPool, uniformBufferWriteData);
}
