#pragma once

#include "../../../Include/VSCommon/VSVersionData.h"
#include "../../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../../Include/VSMain/VSInstanceLayerPacksList.h"

#include <string>
#include <optional>
#include <vector>
#include <memory>
#include <stdint.h>

namespace VulkanSimplified
{
	struct MainInitData;
	struct InstanceCreationData;
}

namespace VulkanSimplified
{
	class SdlEventHandlerInternal;
	class SharedDataMainListInternal;
	class InstanceInternal;

	class MainInternal
	{
	public:
		MainInternal(const MainInitData& initData);
		~MainInternal();

		MainInternal(const MainInternal&) noexcept = delete;
		MainInternal(MainInternal&&) noexcept = delete;

		MainInternal& operator=(const MainInternal&) noexcept = delete;
		MainInternal& operator=(MainInternal&&) noexcept = delete;

		void CreateInstance(const InstanceCreationData& instanceInit);

		SdlEventHandlerInternal& GetSdlEventHandler();
		SharedDataMainListInternal& GetSharedDataMainList();
		InstanceInternal& GetInstance();

		const SdlEventHandlerInternal& GetSdlEventHandler() const;
		const SharedDataMainListInternal& GetSharedDataMainList() const;
		const InstanceInternal& GetInstance() const;

		VersionData GetMaxAvailableVulkanVersion() const;
		InstanceExtensionPacksList GetAvailableInstanceExtensionPacks() const;
		InstanceLayerPacksList GetAvailableInstanceLayerPacks() const;

	private:
		VersionData _maxApiVersion;
		InstanceExtensionPacksList _availableExtensionPacksList;
		InstanceLayerPacksList _availableLayerPacksList;

		std::vector<const char*> _sdlRequired;

		std::unique_ptr<SdlEventHandlerInternal> _eventHandler;
		std::unique_ptr<SharedDataMainListInternal> _sharedData;
		std::unique_ptr<InstanceInternal> _instance;

		uint32_t FindMaximumAvailableVulkanVersion() const;

		InstanceExtensionPacksList CompileAvailableInstanceExtensionPacks() const;
		InstanceLayerPacksList CompileAvailableInstanceLayerPacks() const;

		std::vector<const char*> CompileRequestedInstanceExtensions(const InstanceExtensionPacksList& extensionPacksEnabled,
			const InstanceExtensionPacksList& extensionPacksAvailable) const;
		std::vector<const char*> CompileRequestedInstanceLayers(const InstanceLayerPacksList& layerPacksEnabled,
			const InstanceLayerPacksList& layerPacksAvailable) const;
	};
}