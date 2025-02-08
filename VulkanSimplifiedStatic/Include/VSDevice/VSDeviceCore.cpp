#include "VSDeviceIpch.h"
#include "VSDeviceCore.h"

#include "../../DoNotInclude/VSDevice/VSDeviceCoreInternal.h"

#include "../../DoNotInclude/VSInstance/VSPhysicalDeviceDataInternal.h"

#include "../VSInstance/VSPhysicalDeviceData.h"
#include "../VSInstance/VSDeviceExtensionPacksList.h"

namespace VulkanSimplified
{
	DeviceCore::DeviceCore(VulkanSimplifiedInternal::DeviceCoreInternal& ref) : _internal(ref)
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