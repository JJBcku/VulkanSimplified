#pragma once

#include "VSDeviceVulkan10FeatureFlags.h"

namespace VulkanSimplifiedInternal
{
	class PhysicalDeviceDataInternal;
}

namespace VulkanSimplified
{
	struct DeviceVulkan10Properties;
	struct QueueFamilyData;
	struct FormatsSupportedFeatures;
	struct DeviceExtensionPacksList;
	struct MemoryDataList;
	struct SurfaceSupportData;

	class PhysicalDeviceData
	{
	public:
		PhysicalDeviceData(VulkanSimplifiedInternal::PhysicalDeviceDataInternal& ref);
		~PhysicalDeviceData();

		const DeviceVulkan10Properties& GetVulkan10Properties() const;
		const DeviceVulkan10FeatureFlags& GetVulkan10Features() const;
		const std::vector<QueueFamilyData>& GetVulkanQueueFamiliesData() const;
		const FormatsSupportedFeatures& GetFormatsSupportedFeatures() const;
		const DeviceExtensionPacksList& GetDeviceExtensionPacks() const;
		const MemoryDataList& GetAvailableMemoryDataList() const;
		const std::optional<VulkanSimplified::SurfaceSupportData>& GetSurfaceSupport() const;

	private:
		VulkanSimplifiedInternal::PhysicalDeviceDataInternal& _internal;
	};
}