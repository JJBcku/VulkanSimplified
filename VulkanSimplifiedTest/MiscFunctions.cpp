#include "pch.h"
#include "MiscFunctions.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"

#include <VSMain.h>
#include <SdlEventHandler.h>

#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSDeviceCore.h>

void HandleEvents(VulkanData& data)
{
	auto& base = *data.basicData->vsmain;
	auto eventHandler = base.GetSdlEventHandler();

	eventHandler.HandleEvents();
}

void WaitIdle(VulkanData& data)
{
	auto instance = data.basicData->vsmain->GetInstance();
	auto deviceMain = instance.GetChoosenDevicesMainClass();
	auto deviceCore = deviceMain.GetDeviceCore();
	deviceCore.WaitIdle();
}
