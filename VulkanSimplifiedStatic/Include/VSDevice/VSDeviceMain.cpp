#include "VSDeviceIpch.h"
#include "VSDeviceMain.h"

#include "../../NoInclude/VSDevice/VSDeviceMainInternal.h"

#include "VSDeviceCore.h"

namespace VulkanSimplified
{
	DeviceMain::DeviceMain(VulkanSimplifiedInternal::DeviceMainInternal& ref) : _internal(ref)
	{
	}

	DeviceMain::~DeviceMain()
	{
	}

	DeviceCore DeviceMain::GetDeviceCore()
	{
		return _internal.GetDeviceCore();
	}

	const DeviceCore DeviceMain::GetDeviceCore() const
	{
		return _internal.GetDeviceCore();
	}

}