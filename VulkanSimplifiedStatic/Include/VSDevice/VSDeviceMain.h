#pragma once

namespace VulkanSimplifiedInternal
{
	class DeviceMainInternal;
}

namespace VulkanSimplified
{
	class DeviceCore;
	class WindowList;
	class ShaderLists;

	class DeviceMain
	{
	public:
		DeviceMain(VulkanSimplifiedInternal::DeviceMainInternal& ref);
		~DeviceMain();

		DeviceCore GetDeviceCore();
		WindowList GetWindowList();
		ShaderLists GetShaderLists();

		const DeviceCore GetDeviceCore() const;
		const WindowList GetWindowList() const;
		const ShaderLists GetShaderLists() const;

	private:
		VulkanSimplifiedInternal::DeviceMainInternal& _internal;
	};
}