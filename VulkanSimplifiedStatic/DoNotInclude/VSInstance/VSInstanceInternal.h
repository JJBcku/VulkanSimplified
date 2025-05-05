#pragma once

#include "../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../Include/VSMain/VSInstanceLayerPacksList.h"

#include "../VSDevice/VSDeviceMainInternal.h"

namespace VulkanSimplified
{
	struct LogicalDeviceCreationData;
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplifiedInternal
{
	struct InstanceInternalCreationData;

	class PhysicalDeviceDataInternal;
	class SharedDataMainListInternal;
	class SdlEventHandlerInternal;

	class InstanceInternal
	{
	public:
		InstanceInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, const InstanceInternalCreationData& initData);
		~InstanceInternal();

		InstanceInternal(const InstanceInternal&) noexcept = delete;
		InstanceInternal(InstanceInternal&&) noexcept = delete;

		InstanceInternal& operator=(const InstanceInternal&) noexcept = delete;
		InstanceInternal& operator=(InstanceInternal&&) noexcept = delete;

		size_t GetAvailableDevicesCount() const;

		PhysicalDeviceDataInternal& GetPhysicalDeviceData(size_t deviceIndex);
		DeviceMainInternal& GetChoosenDevicesMainClass();

		const PhysicalDeviceDataInternal& GetPhysicalDeviceData(size_t deviceIndex) const;
		const DeviceMainInternal& GetChoosenDevicesMainClass() const;

		void CreateLogicalDevice(const VulkanSimplified::LogicalDeviceCreationData& creationData, const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities);

	private:
		SdlEventHandlerInternal& _eventHandler;
		const SharedDataMainListInternal& _sharedDataMain;

		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;

		std::string _appName;
		uint32_t _appVersion;
		uint32_t _padding;
		std::string _engineName;
		uint32_t _engineVersion;
		uint32_t _usedVulkanApiVersion;

		VulkanSimplified::InstanceExtensionPacksList _enabledExtensionPacksList;
		VulkanSimplified::InstanceLayerPacksList _enabledLayerPacksList;

		std::vector<PhysicalDeviceDataInternal> _availableDevices;

		std::optional<DeviceMainInternal> _usedDevice;

		void EnumerateDevices();
	};
}