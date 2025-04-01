#include "VSDeviceNIpch.h"
#include "VSDeviceMainInternal.h"

#include "../VSInstance/VsLogicalDeviceInternalCreationData.h"

#include "../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

namespace VulkanSimplifiedInternal
{
	DeviceMainInternal::DeviceMainInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
		const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities) : _core(instance, creationData, physicalDeviceData),
		_windowList(_core, instance, _core.GetDevicesPhysicalData().GetPhysicalDevice(), _core.GetDevice(), initialCapacities.windowList),
		_shaderLists(_core.GetDevice(), initialCapacities.shaderLists)
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

	ShaderListsInternal& DeviceMainInternal::GetShaderLists()
	{
		return _shaderLists;
	}

	const DeviceCoreInternal& DeviceMainInternal::GetDeviceCore() const
	{
		return _core;
	}

	const WindowListInternal& DeviceMainInternal::GetWindowList() const
	{
		return _windowList;
	}

	const ShaderListsInternal& DeviceMainInternal::GetShaderLists() const
	{
		return _shaderLists;
	}

}