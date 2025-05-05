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

	class DescriptorDataList;
	class RenderPassList;
	class PipelineDataLists;

	class MemoryObjectsList;
	class ImageDataLists;

	class SynchronizationDataLists;
	class CommandPoolMainList;

	class DeviceMain
	{
	public:
		DeviceMain(VulkanSimplifiedInternal::DeviceMainInternal& ref);
		~DeviceMain();

		DeviceCore GetDeviceCore();
		WindowList GetWindowList();
		ShaderLists GetShaderLists();

		DescriptorDataList GetDescriptorDataLists();
		RenderPassList GetRenderPassList();
		PipelineDataLists GetPipelineDataLists();

		MemoryObjectsList GetMemoryObjectsList();
		ImageDataLists GetImageDataLists();

		SynchronizationDataLists GetSynchronizationDataLists();
		CommandPoolMainList GetCommandPoolMainList();

		const DeviceCore GetDeviceCore() const;
		const WindowList GetWindowList() const;
		const ShaderLists GetShaderLists() const;

		const DescriptorDataList GetDescriptorDataLists() const;
		const RenderPassList GetRenderPassList() const;
		const PipelineDataLists GetPipelineDataLists() const;

		const MemoryObjectsList GetMemoryObjectsList() const;
		const ImageDataLists GetImageDataLists() const;

		const SynchronizationDataLists GetSynchronizationDataLists() const;
		const CommandPoolMainList GetCommandPoolMainList() const;

	private:
		VulkanSimplifiedInternal::DeviceMainInternal& _internal;
	};
}