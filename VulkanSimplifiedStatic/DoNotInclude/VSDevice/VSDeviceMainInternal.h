#pragma once

#include "VSDeviceCoreInternal.h"
#include "VSWindowListInternal.h"
#include "VSShaderListsInternal.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData;
	class PhysicalDeviceDataInternal;

	class DeviceMainInternal
	{
	public:
		DeviceMainInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
			const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities);
		~DeviceMainInternal();

		DeviceCoreInternal& GetDeviceCore();
		WindowListInternal& GetWindowList();
		ShaderListsInternal& GetShaderLists();

		const DeviceCoreInternal& GetDeviceCore() const;
		const WindowListInternal& GetWindowList() const;
		const ShaderListsInternal& GetShaderLists() const;

	private:
		DeviceCoreInternal _core;
		WindowListInternal _windowList;
		ShaderListsInternal _shaderLists;
	};
}