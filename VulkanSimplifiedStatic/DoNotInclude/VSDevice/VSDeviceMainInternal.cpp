#include "VSDeviceNIpch.h"
#include "VSDeviceMainInternal.h"

#include "../VSInstance/VsLogicalDeviceInternalCreationData.h"

namespace VulkanSimplifiedInternal
{
	DeviceMainInternal::DeviceMainInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData) :
		_core(instance, creationData, physicalDeviceData)
	{
	}

	DeviceMainInternal::~DeviceMainInternal()
	{
	}

	DeviceCoreInternal& DeviceMainInternal::GetDeviceCore()
	{
		return _core;
	}

	const DeviceCoreInternal& DeviceMainInternal::GetDeviceCore() const
	{
		return _core;
	}

}