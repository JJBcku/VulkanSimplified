#include "VSDeviceIpch.h"
#include "VSDeviceMain.h"

#include "../../DoNotInclude/VSDevice/VSDeviceMainInternal.h"

#include "VSDeviceCore.h"
#include "VSWindowList.h"
#include "VSShaderLists.h"
#include "VSDescriptorDataList.h"
#include "VSRenderPassDataList.h"

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

	RenderPassList DeviceMain::GetRenderPassList()
	{
		return _internal.GetRenderPassList();
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

	const RenderPassList DeviceMain::GetRenderPassList() const
	{
		return _internal.GetRenderPassList();
	}

}