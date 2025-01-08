#include "VSInstanceIpch.h"
#include "VSPhysicalDeviceData.h"

#include "../../NoInclude/VSInstance/VSPhysicalDeviceDataInternal.h"

namespace VulkanSimplified
{

	PhysicalDeviceData::PhysicalDeviceData(VulkanSimplifiedInternal::PhysicalDeviceDataInternal& ref) : _internal(ref)
	{
	}

	PhysicalDeviceData::~PhysicalDeviceData()
	{
	}

	const VulkanSimplified::DeviceVulkan10Properties& PhysicalDeviceData::GetVulkan10Properties() const
	{
		return _internal.GetVulkan10Properties();
	}

	const VulkanSimplified::DeviceVulkan10FeatureFlags& PhysicalDeviceData::GetVulkan10Features() const
	{
		return _internal.GetVulkan10Features();
	}

	const std::vector<VulkanSimplified::QueueFamilyData>& PhysicalDeviceData::GetVulkanQueueFamiliesData() const
	{
		return _internal.GetVulkanQueueFamiliesData();
	}

	const VulkanSimplified::FormatsSupportedFeatures& PhysicalDeviceData::GetFormatsSupportedFeatures() const
	{
		return _internal.GetFormatsSupportedFeatures();
	}

	const VulkanSimplified::DeviceExtensionPacksList& PhysicalDeviceData::GetDeviceExtensionPacks() const
	{
		return _internal.GetDeviceExtensionPacks();
	}

	const VulkanSimplified::MemoryDataList& PhysicalDeviceData::GetAvailableMemoryDataList() const
	{
		return _internal.GetAvailableMemoryDataList();
	}

	const std::optional<VulkanSimplified::SurfaceSupportData>& PhysicalDeviceData::GetSurfaceSupport() const
	{
		return _internal.GetSurfaceSupport();
	}

}