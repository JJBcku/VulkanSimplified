#pragma once

#include "VSDeviceCoreInternal.h"
#include "VSWindowListInternal.h"
#include "VSShaderListsInternal.h"

#include "VSDescriptorDataListInternal.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData;
	class PhysicalDeviceDataInternal;
	class SharedDataMainListInternal;

	class DeviceMainInternal
	{
	public:
		DeviceMainInternal(const SharedDataMainListInternal& sharedDataMain, VkInstance instance, const LogicalDeviceInternalCreationData& creationData,
			const PhysicalDeviceDataInternal& physicalDeviceData, const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities);
		~DeviceMainInternal();

		DeviceCoreInternal& GetDeviceCore();
		WindowListInternal& GetWindowList();
		ShaderListsInternal& GetShaderLists();

		DescriptorDataListInternal& GetDescriptorDataLists();

		const DeviceCoreInternal& GetDeviceCore() const;
		const WindowListInternal& GetWindowList() const;
		const ShaderListsInternal& GetShaderLists() const;

		const DescriptorDataListInternal& GetDescriptorDataLists() const;

	private:
		const SharedDataMainListInternal& _sharedDataMain;

		DeviceCoreInternal _core;
		WindowListInternal _windowList;
		ShaderListsInternal _shaderLists;

		DescriptorDataListInternal _descriptorLists;
	};
}