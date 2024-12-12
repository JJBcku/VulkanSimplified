#pragma once

#include "EventHandler/SdlEventHandlerInternal.h"

#include <string>

#include "../../Include/VSCommon/VulkanVersionData.h"
#include "../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../Include/VSMain/VSInstanceLayerPacksList.h"

namespace VulkanSimplified
{
	struct MainInitData;
}

namespace VulkanSimplifiedInternal
{
	class MainInternal
	{
	public:
		MainInternal(const VulkanSimplified::MainInitData& initData);
		~MainInternal();

		SdlEventHandlerInternal& GetSdlEventHandler();

		const SdlEventHandlerInternal& GetSdlEventHandler() const;

		VulkanSimplified::VulkanVersionData GetAppVersion() const;
		VulkanSimplified::VulkanVersionData GetMaxAvailableVulkanVersion() const;
		VulkanSimplified::InstanceExtensionPacksList GetAvailableInstanceExtensionPacks() const;
		VulkanSimplified::InstanceLayerPacksList GetAvailableInstanceLayerPacks() const;

	private:
		std::string _appName;
		std::string _appVariantName;
		VulkanSimplified::VulkanVersionData _appVersion;
		std::string _engineName;
		VulkanSimplified::VulkanVersionData _engineVersion;

		VulkanSimplified::VulkanVersionData _maxApiVersion;
		VulkanSimplified::InstanceExtensionPacksList _availableExtensionPacksList;
		VulkanSimplified::InstanceLayerPacksList _availableLayerPacksList;

		SdlEventHandlerInternal _eventHandler;

		uint32_t FindMaximumAvailableVulkanVersion() const;

		VulkanSimplified::InstanceExtensionPacksList CompileAvailableInstanceExtensionPacks() const;
		VulkanSimplified::InstanceLayerPacksList CompileAvailableInstanceLayerPacks() const;
	};
}