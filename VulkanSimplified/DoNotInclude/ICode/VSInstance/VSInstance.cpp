#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSInstance.h"

#include "../../../DoNotInclude/DNIData/VSInstance/VSInstanceInternal.h"

#include "../../../Include/VSInstance/VSPhysicalDeviceData.h"
#include "../../../Include/VSDevice/VSDeviceMain.h"

#include "../../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

#include "../../../Include/VSCommon/VSVersionData.h"

namespace VulkanSimplified
{
	Instance::Instance(InstanceInternal& ref) : _internal(ref)
	{
	}

	Instance::~Instance()
	{
	}

	const std::string& Instance::GetAppFullName() const
	{
		return _internal.GetAppFullName();
	}

	const std::string& Instance::GetEngineFullName() const
	{
		return _internal.GetEngineFullName();
	}

	VersionData Instance::GetAppVersion() const
	{
		return _internal.GetAppVersion();
	}

	VersionData Instance::GetEngineVersion() const
	{
		return _internal.GetEngineVersion();
	}

	size_t Instance::GetAvailableDevicesCount() const
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

	void Instance::RecreateLogicalDevice(const LogicalDeviceCreationData& creationData, const DeviceInitialCapacitiesList& initialCapacities)
	{
		_internal.RecreateLogicalDevice(creationData, initialCapacities);
	}

}
