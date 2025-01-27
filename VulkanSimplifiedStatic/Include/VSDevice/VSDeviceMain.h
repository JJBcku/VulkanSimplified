#pragma once

namespace VulkanSimplifiedInternal
{
	class DeviceMainInternal;
}

namespace VulkanSimplified
{
	class DeviceCore;
	class WindowList;

	class DeviceMain
	{
	public:
		DeviceMain(VulkanSimplifiedInternal::DeviceMainInternal& ref);
		~DeviceMain();

		DeviceCore GetDeviceCore();
		WindowList GetWindowList();

		const DeviceCore GetDeviceCore() const;
		const WindowList GetWindowList() const;

	private:
		VulkanSimplifiedInternal::DeviceMainInternal& _internal;
	};
}