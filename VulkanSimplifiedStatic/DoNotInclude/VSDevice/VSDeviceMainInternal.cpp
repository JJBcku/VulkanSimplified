#include "VSDeviceNIpch.h"
#include "VSDeviceMainInternal.h"

#include "../VSInstance/VsLogicalDeviceInternalCreationData.h"

#include "../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

namespace VulkanSimplifiedInternal
{
	DeviceMainInternal::DeviceMainInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
		const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities) : _core(instance, creationData, physicalDeviceData), _windowList(initialCapacities.windowList)
	{
	}

	DeviceMainInternal::~DeviceMainInternal()
	{
	}

	DeviceCoreInternal& DeviceMainInternal::GetDeviceCore()
	{
		return _core;
	}

	WindowListInternal& DeviceMainInternal::GetWindowList()
	{
		return _windowList;
	}

	const DeviceCoreInternal& DeviceMainInternal::GetDeviceCore() const
	{
		return _core;
	}

	const WindowListInternal& DeviceMainInternal::GetWindowList() const
	{
		return _windowList;
	}

}