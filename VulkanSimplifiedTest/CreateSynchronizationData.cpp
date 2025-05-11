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

	synchro.inFlightFences.reserve(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		synchro.inFlightFences.push_back(synchronizationData.AddFence());
	}

	synchro.imageAvailableSemaphores.reserve(framesInFlight);
	synchro.renderingFinishedSemaphores.reserve(framesInFlight);
	synchro.queueTransferFinishedSemaphores.reserve(framesInFlight);
	synchro.dataTransferFinishedSemaphores.reserve(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		synchro.imageAvailableSemaphores.push_back(synchronizationData.AddSemaphore());
		synchro.renderingFinishedSemaphores.push_back(synchronizationData.AddSemaphore());
		synchro.queueTransferFinishedSemaphores.push_back(synchronizationData.AddSemaphore());
		synchro.dataTransferFinishedSemaphores.push_back(synchronizationData.AddSemaphore());
	}
}
