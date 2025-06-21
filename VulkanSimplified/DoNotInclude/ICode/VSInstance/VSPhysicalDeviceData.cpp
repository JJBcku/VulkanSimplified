#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSPhysicalDeviceData.h"

#include "../../../DoNotInclude/DNIData/VSInstance/VSPhysicalDeviceDataInternal.h"

namespace VulkanSimplified
{

	PhysicalDeviceData::PhysicalDeviceData(PhysicalDeviceDataInternal& ref) : _internal(ref)
	{
	}

	PhysicalDeviceData::~PhysicalDeviceData()
	{
	}

	const DeviceVulkan10Properties& PhysicalDeviceData::GetVulkan10Properties() const
	{
		return _internal.GetVulkan10Properties();
	}

	const DeviceVulkan10FeatureFlags& PhysicalDeviceData::GetVulkan10Features() const
	{
		return _internal.GetVulkan10Features();
	}

	const std::vector<QueueFamilyData>& PhysicalDeviceData::GetVulkanQueueFamiliesData() const
	{
		return _internal.GetVulkanQueueFamiliesData();
	}

	const FormatsSupportedFeatures& PhysicalDeviceData::GetFormatsSupportedFeatures() const
	{
		return _internal.GetFormatsSupportedFeatures();
	}

	const DeviceExtensionPacksList& PhysicalDeviceData::GetDeviceExtensionPacks() const
	{
		return _internal.GetDeviceExtensionPacks();
	}

	const MemoryDataList& PhysicalDeviceData::GetAvailableMemoryDataList() const
	{
		return _internal.GetAvailableMemoryDataList();
	}

	const std::optional<SurfaceSupportData>& PhysicalDeviceData::GetSurfaceSupport() const
	{
		return _internal.GetSurfaceSupport();
	}

}