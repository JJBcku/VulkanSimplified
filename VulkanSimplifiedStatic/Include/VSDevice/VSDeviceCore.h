#pragma once

#include "../VSInstance/VSDeviceVulkan10FeatureFlags.h"

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
}

namespace VulkanSimplified
{
	struct DeviceExtensionPacksList;

	class PhysicalDeviceData;

	class DeviceCore
	{
	public:
		DeviceCore(VulkanSimplifiedInternal::DeviceCoreInternal& ref);
		~DeviceCore();

		DeviceCore(const DeviceCore&) noexcept = delete;

		DeviceCore& operator=(const DeviceCore&) noexcept = delete;

		uint32_t GetDevicesApiVersion() const;
		uint32_t GetQueuesFamily(size_t queueIndex) const;

		DeviceVulkan10FeatureFlags GetVulkan10EnabledFeatures() const;
		const DeviceExtensionPacksList& GetDevicesEnabledExtensionPacks() const;

		PhysicalDeviceData GetDevicesPhysicalData();

		const PhysicalDeviceData GetDevicesPhysicalData() const;

		void WaitIdle() const;

	private:
		VulkanSimplifiedInternal::DeviceCoreInternal& _internal;
	};
}