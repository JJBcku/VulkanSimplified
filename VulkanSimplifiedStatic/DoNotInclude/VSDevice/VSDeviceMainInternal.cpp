#include "VSDeviceNIpch.h"
#include "VSDeviceMainInternal.h"

#include "../VSInstance/VsLogicalDeviceInternalCreationData.h"

#include "../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

#include  "../VSSharedData/VSSharedDataMainListInternal.h"

namespace VulkanSimplifiedInternal
{
	DeviceMainInternal::DeviceMainInternal(const SharedDataMainListInternal& sharedDataMain, VkInstance instance, const LogicalDeviceInternalCreationData& creationData,
		const PhysicalDeviceDataInternal& physicalDeviceData, const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities) : _sharedDataMain(sharedDataMain),
		_core(instance, creationData, physicalDeviceData),
		_windowList(_core, instance, _core.GetDevicesPhysicalData().GetPhysicalDevice(), _core.GetDevice(), initialCapacities.windowList),
		_shaderLists(_core.GetDevice(), initialCapacities.shaderLists), _descriptorLists(_sharedDataMain.GetDescriptorDataList(), _core.GetDevice(), initialCapacities.descriptorLists),
		_renderPassList(_sharedDataMain.GetRenderPassDataList(), _core.GetDevice(), initialCapacities.renderPassLists)
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

	DescriptorDataListInternal& DeviceMainInternal::GetDescriptorDataLists()
	{
		return _descriptorLists;
	}

	RenderPassListInternal& DeviceMainInternal::GetRenderPassList()
	{
		return _renderPassList;
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

	const DescriptorDataListInternal& DeviceMainInternal::GetDescriptorDataLists() const
	{
		return _descriptorLists;
	}

	const RenderPassListInternal& DeviceMainInternal::GetRenderPassList() const
	{
		return _renderPassList;
	}

}