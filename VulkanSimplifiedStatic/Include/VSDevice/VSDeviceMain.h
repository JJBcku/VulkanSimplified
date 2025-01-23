#pragma once

namespace VulkanSimplifiedInternal
{
	class DeviceMainInternal;
}

namespace VulkanSimplified
{
	class DeviceCore;

	class DeviceMain
	{
	public:
		DeviceMain(VulkanSimplifiedInternal::DeviceMainInternal& ref);
		~DeviceMain();

		DeviceCore GetDeviceCore();

		const DeviceCore GetDeviceCore() const;

	private:
		VulkanSimplifiedInternal::DeviceMainInternal& _internal;
	};
}