#include "pch.h"
#include "CreateBasicData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"

#include "VSMain.h"
#include "VSMainInitData.h"

#include "MainSettings.h"

#include "EventHandler/SdlEventHandler.h"
#include "EventHandler/SdlQuitEventData.h"

#include "CustomLists/IDObject.h"

#include <functional>

void CreateBasicData(VulkanData& data, MainSettings& settings)
{
	data.basicData = std::make_unique<VulkanBasicData>();
	
	VulkanSimplified::VSMainInitData basicInit;

	data.basicData->vsmain.emplace(basicInit);
	auto& main = data.basicData->vsmain.value();
	auto eventHandler = main.GetSdlEventHandler();

	eventHandler.RegisterQuitEventCallback(MainSettings::QuitEventCallback, &settings, 1);
}
