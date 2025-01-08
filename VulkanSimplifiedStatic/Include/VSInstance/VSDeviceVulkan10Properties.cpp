#include "VSInstanceIpch.h"
#include "VSDeviceVulkan10Properties.h"

namespace VulkanSimplified
{
	DeviceVulkan10Properties::DeviceVulkan10Properties()
	{
		apiMaxSupportedVersion = 0;
		driverVersion = 0;
		vendorID = 0;
		deviceID = 0;
		deviceType = DeviceType::OTHER;

		std::memset(pipelineCacheUUID.data(), 0, pipelineCacheUUID.size() * sizeof(pipelineCacheUUID[0]));
	}

	DeviceVulkan10Properties::~DeviceVulkan10Properties()
	{
	}
}