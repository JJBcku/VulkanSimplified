#pragma once

#include "VSDeviceCoreInternal.h"

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData;
	class PhysicalDeviceDataInternal;

	class DeviceMainInternal
	{
	public:
		DeviceMainInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData);
		~DeviceMainInternal();

		DeviceCoreInternal& GetDeviceCore();

		const DeviceCoreInternal& GetDeviceCore() const;

	private:
		DeviceCoreInternal _core;
	};
}