#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSInstance.h"

#include "../../../DoNotInclude/DNIHeaders/VSInstance/VSInstanceInternal.h"

#include "../../../Include/VSInstance/VSPhysicalDeviceData.h"
#include "../../../Include/VSDevice/VSDeviceMain.h"

#include "../../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

namespace VulkanSimplified
{
	Instance::Instance(VulkanSimplifiedInternal::InstanceInternal& ref) : _internal(ref)
	{
	}

	Instance::~Instance()
	{
	}

	size_t VulkanSimplified::Instance::GetAvailableDevicesCount() const
	{
		return _internal.GetAvailableDevicesCount();
	}

	PhysicalDeviceData Instance::GetPhysicalDeviceData(size_t deviceIndex)
	{
		return _internal.GetPhysicalDeviceData(deviceIndex);
	}

	DeviceMain Instance::GetChoosenDevicesMainClass()
	{
		return _internal.GetChoosenDevicesMainClass();
	}

	const PhysicalDeviceData Instance::GetPhysicalDeviceData(size_t deviceIndex) const
	{
		return _internal.GetPhysicalDeviceData(deviceIndex);
	}

	const DeviceMain Instance::GetChoosenDevicesMainClass() const
	{
		return _internal.GetChoosenDevicesMainClass();
	}

	void Instance::CreateLogicalDevice(const LogicalDeviceCreationData& creationData, const DeviceInitialCapacitiesList& initialCapacities)
	{
		_internal.CreateLogicalDevice(creationData, initialCapacities);
	}

}
