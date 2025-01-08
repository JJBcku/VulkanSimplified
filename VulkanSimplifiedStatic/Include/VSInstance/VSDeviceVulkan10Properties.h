#pragma once

#include "VSDeviceVulkan10Limits.h"

namespace VulkanSimplified
{
	enum class DeviceType : uint64_t
	{
		OTHER,
		INTERGRATED_GPU,
		DISCRETE_GPU,
		VIRTUAL_GPU,
		CPU,
	};

	struct DeviceVulkan10Properties
	{
		std::uint32_t apiMaxSupportedVersion;
		std::uint32_t driverVersion;
		std::uint32_t vendorID;
		std::uint32_t deviceID;
		DeviceType deviceType;
		std::string deviceName;
		std::array<std::uint8_t, 16> pipelineCacheUUID;

		DeviceVulkan10Limits limits;

		DeviceVulkan10Properties();
		~DeviceVulkan10Properties();
	};
}
