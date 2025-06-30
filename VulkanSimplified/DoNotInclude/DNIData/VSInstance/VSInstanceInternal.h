#pragma once

#include "../../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../../Include/VSMain/VSInstanceLayerPacksList.h"

#include "../../../Include/VSCommon/VSVersionData.h"

#include <string>
#include <stdint.h>
#include <vector>
#include <memory>

typedef struct VkInstance_T* VkInstance;
typedef struct VkDebugUtilsMessengerEXT_T* VkDebugUtilsMessengerEXT;

namespace VulkanSimplified
{
	struct LogicalDeviceCreationData;
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplified
{
	struct InstanceInternalCreationData;

	class SharedDataMainListInternal;
	class SdlEventHandlerInternal;

	class PhysicalDeviceDataInternal;
	class DeviceMainInternal;

	class InstanceInternal
	{
	public:
		InstanceInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, const InstanceInternalCreationData& initData);
		~InstanceInternal();

		InstanceInternal(const InstanceInternal&) noexcept = delete;
		InstanceInternal(InstanceInternal&&) noexcept = delete;

		InstanceInternal& operator=(const InstanceInternal&) noexcept = delete;
		InstanceInternal& operator=(InstanceInternal&&) noexcept = delete;

		const std::string& GetAppFullName() const;
		const std::string& GetEngineFullName() const;

		VersionData GetAppVersion() const;
		VersionData GetEngineVersion() const;

		size_t GetAvailableDevicesCount() const;

		PhysicalDeviceDataInternal& GetPhysicalDeviceData(size_t deviceIndex);
		DeviceMainInternal& GetChoosenDevicesMainClass();

		const PhysicalDeviceDataInternal& GetPhysicalDeviceData(size_t deviceIndex) const;
		const DeviceMainInternal& GetChoosenDevicesMainClass() const;

		void CreateLogicalDevice(const LogicalDeviceCreationData& creationData, const DeviceInitialCapacitiesList& initialCapacities);
		void RecreateLogicalDevice(const LogicalDeviceCreationData& creationData, const DeviceInitialCapacitiesList& initialCapacities);

	private:
		SdlEventHandlerInternal& _eventHandler;
		const SharedDataMainListInternal& _sharedDataMain;

		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;

		std::string _appName;
		VersionData _appVersion;
		std::string _engineName;
		VersionData _engineVersion;
		uint32_t _usedVulkanApiVersion;
		uint32_t _padding;

		InstanceExtensionPacksList _enabledExtensionPacksList;
		InstanceLayerPacksList _enabledLayerPacksList;

		std::vector<PhysicalDeviceDataInternal> _availableDevices;

		std::unique_ptr<DeviceMainInternal> _usedDevice;

		void EnumerateDevices();
	};
}