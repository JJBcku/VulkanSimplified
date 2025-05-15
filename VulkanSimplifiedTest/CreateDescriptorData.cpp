#include "pch.h"
#include "CreateDescriptorData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanDescriptorData.h"

#include "SwapchainSizes.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSDescriptorDataLists.h>

#include <VSDescriptorTypeFlags.h>

void CreateDescriptorData(VulkanData& data)
{
	data.descriptorData = std::make_unique<VulkanDescriptorData>();

	auto descriptorDataList = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass().GetDescriptorDataLists();

	data.descriptorData->descriptorPool = descriptorDataList.AddNoIndividualFreeingDescriptorPool(framesInFlight,
		{ {VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER, framesInFlight} });
}
