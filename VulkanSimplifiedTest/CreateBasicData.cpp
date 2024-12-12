#include "pch.h"
#include "CreateBasicData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"

#include "VSMain.h"
#include "VSMainInitData.h"

#include "MainSettings.h"

#include "SdlEventHandler.h"
#include "SdlQuitEventData.h"

#include "VSInstanceExtensionPacksList.h"
#include "VSInstanceLayerPacksList.h"

#include "CustomLists/IDObject.h"

#include <functional>
#include <stdexcept>

void CreateBasicData(VulkanData& data, MainSettings& settings)
{
	data.basicData = std::make_unique<VulkanBasicData>();
	
	VulkanSimplified::MainInitData basicInit;
	basicInit.engineVersion.SetVulkanPatchVersion(2);

	basicInit.appVersion = basicInit.engineVersion;

	data.basicData->vsmain.emplace(basicInit);
	auto& main = data.basicData->vsmain.value();

	auto availableExtensionPacks = main.GetAvailableInstanceExtensionPacks();
	auto availableLayerPacks = main.GetAvailableInstanceLayerPacks();

	if (!availableExtensionPacks.sdlRequiredExtensions)
		throw std::runtime_error("CreateBasicData Error: SDL required instance extensions are not available!");

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	if (!availableExtensionPacks.debugUtils)
		throw std::runtime_error("CreateBasicData Error: debugging instance extensions are not available!");

	if (!availableLayerPacks.debugUtils)
		throw std::runtime_error("CreateBasicData Error: debugging layers are not available!");
#endif

	auto eventHandler = main.GetSdlEventHandler();

	eventHandler.RegisterQuitEventCallback(MainSettings::QuitEventCallback, &settings, 1);
}
