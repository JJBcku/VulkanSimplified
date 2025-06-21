#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDeviceCore.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSDeviceCoreInternal.h"

#include "../../../DoNotInclude/DNIData/VSInstance/VSPhysicalDeviceDataInternal.h"

#include "../../../Include/VSInstance/VSPhysicalDeviceData.h"
#include "../../../Include/VSInstance/VSDeviceExtensionPacksList.h"

namespace VulkanSimplified
{
	DeviceCore::DeviceCore(DeviceCoreInternal& ref) : _internal(ref)
	{
	}

	DeviceCore::~DeviceCore()
	{
	}

	uint32_t DeviceCore::GetDevicesApiVersion() const
	{
		return _internal.GetDevicesApiVersion();
	}

	uint32_t DeviceCore::GetQueuesFamily(size_t queueIndex) const
	{
		return _internal.GetQueuesFamily(queueIndex);
	}

	DeviceVulkan10FeatureFlags DeviceCore::GetVulkan10EnabledFeatures() const
	{
		return _internal.GetVulkan10EnabledFeatures();
	}

	const DeviceExtensionPacksList& DeviceCore::GetDevicesEnabledExtensionPacks() const
	{
		return _internal.GetDevicesEnabledExtensionPacks();
	}

	PhysicalDeviceData DeviceCore::GetDevicesPhysicalData()
	{
		return _internal.GetDevicesPhysicalData();
	}

	const PhysicalDeviceData DeviceCore::GetDevicesPhysicalData() const
	{
		return _internal.GetDevicesPhysicalData();
	}

	void DeviceCore::WaitIdle() const
	{
		_internal.WaitIdle();
	}

}