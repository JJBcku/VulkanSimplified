#pragma once

#include "EventHandler/SdlEventHandlerInternal.h"

#include <string>

#include "../../Include/VSCommon/VSVersionData.h"
#include "../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../Include/VSMain/VSInstanceLayerPacksList.h"

#include "../VSInstance/VSInstanceInternal.h"

namespace VulkanSimplified
{
	struct MainInitData;
	struct InstanceCreationData;
}

namespace VulkanSimplifiedInternal
{
	class InstanceInternal;

	class MainInternal
	{
	public:
		MainInternal(const VulkanSimplified::MainInitData& initData);
		~MainInternal();

		MainInternal(const MainInternal&) noexcept = delete;
		MainInternal(MainInternal&&) noexcept = delete;

		MainInternal& operator=(const MainInternal&) noexcept = delete;
		MainInternal& operator=(MainInternal&&) noexcept = delete;

		void CreateInstance(const VulkanSimplified::InstanceCreationData& instanceInit);

		SdlEventHandlerInternal& GetSdlEventHandler();
		InstanceInternal& GetInstance();

		const SdlEventHandlerInternal& GetSdlEventHandler() const;
		const InstanceInternal& GetInstance() const;

		VulkanSimplified::VersionData GetAppVersion() const;
		VulkanSimplified::VersionData GetMaxAvailableVulkanVersion() const;
		VulkanSimplified::InstanceExtensionPacksList GetAvailableInstanceExtensionPacks() const;
		VulkanSimplified::InstanceLayerPacksList GetAvailableInstanceLayerPacks() const;

	private:
		std::string _appName;
		std::string _appVariantName;
		VulkanSimplified::VersionData _appVersion;
		std::string _engineName;
		VulkanSimplified::VersionData _engineVersion;

		VulkanSimplified::VersionData _maxApiVersion;
		VulkanSimplified::InstanceExtensionPacksList _availableExtensionPacksList;
		VulkanSimplified::InstanceLayerPacksList _availableLayerPacksList;

		std::vector<const char*> _sdlRequired;

		SdlEventHandlerInternal _eventHandler;
		std::optional<InstanceInternal> _instance;

		uint32_t FindMaximumAvailableVulkanVersion() const;

		VulkanSimplified::InstanceExtensionPacksList CompileAvailableInstanceExtensionPacks() const;
		VulkanSimplified::InstanceLayerPacksList CompileAvailableInstanceLayerPacks() const;

		std::vector<const char*> CompileRequestedInstanceExtensions(const VulkanSimplified::InstanceExtensionPacksList& extensionPacksEnabled,
			const VulkanSimplified::InstanceExtensionPacksList& extensionPacksAvailable) const;
		std::vector<const char*> CompileRequestedInstanceLayers(const VulkanSimplified::InstanceLayerPacksList& layerPacksEnabled,
			const VulkanSimplified::InstanceLayerPacksList& layerPacksAvailable) const;
	};
}