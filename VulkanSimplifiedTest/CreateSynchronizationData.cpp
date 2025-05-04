#include "pch.h"
#include "CreateSynchronizationData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanSynchronizationData.h"

#include "SwapchainSizes.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSSynchronizationDataLists.h>

void CreateSynchronizationData(VulkanData& data)
{
	auto synchronizationData = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass().GetSynchronizationDataLists();

	data.synchronizationData = std::make_unique<VulkanSynchronizationData>();
	auto& synchro = *data.synchronizationData;

	synchro.inFlightFence.reserve(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		synchro.inFlightFence.push_back(synchronizationData.AddFence());
	}

	synchro.imageAvailableSemaphore.reserve(framesInFlight);
	synchro.renderingFinishedSemaphore.reserve(framesInFlight);
	synchro.transferFinishedSemaphore.reserve(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		synchro.imageAvailableSemaphore.push_back(synchronizationData.AddSemaphore());
		synchro.renderingFinishedSemaphore.push_back(synchronizationData.AddSemaphore());
		synchro.transferFinishedSemaphore.push_back(synchronizationData.AddSemaphore());
	}
}
