#pragma once

#include "../../../Include/VSInstance/VSDeviceVulkan10FeatureFlagsDef.h"
#include "../../../Include/VSInstance/VSDeviceExtensionPacksList.h"

#include "../VSInstance/VSPhysicalDeviceDataInternal.h"

#include <stdint.h>
#include <vector>
#include <utility>

typedef struct VkInstance_T* VkInstance;
typedef struct VkDevice_T* VkDevice;
typedef struct VkQueue_T* VkQueue;

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData;

	class DeviceCoreInternal
	{
	public:
		DeviceCoreInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData);
		~DeviceCoreInternal();

		DeviceCoreInternal(const DeviceCoreInternal&) noexcept = delete;
		DeviceCoreInternal(DeviceCoreInternal&&) noexcept = delete;

		DeviceCoreInternal& operator=(const DeviceCoreInternal&) noexcept = delete;
		DeviceCoreInternal& operator=(DeviceCoreInternal&&) noexcept = delete;

		VkDevice GetDevice() const;
		uint32_t GetDevicesApiVersion() const;

		VkQueue GetQueue(size_t queueIndex) const;
		uint32_t GetQueuesFamily(size_t queueIndex) const;
		std::vector<uint32_t> GetQueuesFamilies(const std::vector<size_t>& queueIndex) const;

		VulkanSimplified::DeviceVulkan10FeatureFlags GetVulkan10EnabledFeatures() const;
		const VulkanSimplified::DeviceExtensionPacksList& GetDevicesEnabledExtensionPacks() const;

		PhysicalDeviceDataInternal& GetDevicesPhysicalData();

		const PhysicalDeviceDataInternal& GetDevicesPhysicalData() const;

		void WaitIdle() const;

	private:
		VkInstance _instance;
		VkDevice _device;

		std::vector<std::pair<VkQueue, uint32_t>> _queues;

		uint32_t _apiVersion;
		uint32_t _padding;

		VulkanSimplified::DeviceVulkan10FeatureFlags _vulkan10EnabledFeatures;
		VulkanSimplified::DeviceExtensionPacksList _requestedExtensionPacks;

		PhysicalDeviceDataInternal _physicalDeviceData;
	};
}