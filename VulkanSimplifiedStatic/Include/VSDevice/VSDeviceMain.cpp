#include "VSDeviceIpch.h"
#include "VSDeviceMain.h"

#include "../../DoNotInclude/VSDevice/VSDeviceMainInternal.h"
#include "../../DoNotInclude/VSDevice/VSWindowListInternal.h"
#include "../../DoNotInclude/VSDevice/VSShaderListsInternal.h"
#include "../../DoNotInclude/VSDevice/VSDescriptorDataListInternal.h"

#include "VSDeviceCore.h"
#include "VSWindowList.h"
#include "VSShaderLists.h"
#include "VSDescriptorDataList.h"

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

	WindowList DeviceMain::GetWindowList()
	{
		return _internal.GetWindowList();
	}

	ShaderLists DeviceMain::GetShaderLists()
	{
		return _internal.GetShaderLists();
	}

	DescriptorDataList DeviceMain::GetDescriptorDataLists()
	{
		return _internal.GetDescriptorDataLists();
	}

	const DeviceCore DeviceMain::GetDeviceCore() const
	{
		return _internal.GetDeviceCore();
	}

	const WindowList DeviceMain::GetWindowList() const
	{
		return _internal.GetWindowList();
	}

	const ShaderLists DeviceMain::GetShaderLists() const
	{
		return _internal.GetShaderLists();
	}

	const DescriptorDataList DeviceMain::GetDescriptorDataLists() const
	{
		return _internal.GetDescriptorDataLists();
	}

}