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

#include "VSInstanceCreationData.h"
#include "VSInstance.h"

#include "CustomLists/IDObject.h"

#include <functional>

void CreateBasicData(VulkanData& data, MainSettings& settings)
{
	data.basicData = std::make_unique<VulkanBasicData>();
	
	VS::MainInitData basicInit;

	data.basicData->vsmain = std::make_unique<VS::Main>(basicInit);
	auto& main = *data.basicData->vsmain;

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

	VS::InstanceCreationData instanceInit;
	instanceInit.engineVersion.SetVulkanPatchVersion(0);
	instanceInit.engineVersion.SetVulkanMinorVersion(0);
	instanceInit.engineVersion.SetVulkanMajorVersion(1);

	instanceInit.appVersion = instanceInit.engineVersion;

	instanceInit.appName = "VulkanSimplified Test";
	
#if defined(_DEBUG) || defined(DEBUG)
	instanceInit.appVariantName = "x64 Debug";
#else
#if defined(DEBUG_UTILS)
	instanceInit.appVariantName = "x64 RelWithDebugUtils";
#else
	instanceInit.appVariantName = "x64 Release";
#endif
#endif

	instanceInit.engineName = "Vulkan Simplified";

	instanceInit.usedVulkanApiVersion = VS::VersionData(0, 1, 0, 0);
	instanceInit.enabledExtensionPacks.sdlRequiredExtensions = true;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	instanceInit.enabledExtensionPacks.debugUtils = true;

	instanceInit.enabledLayerPacks.debugUtils = true;
#endif

	main.CreateInstance(instanceInit);
}
