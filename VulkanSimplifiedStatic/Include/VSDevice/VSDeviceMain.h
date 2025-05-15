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

	class DescriptorDataLists;
	class RenderPassList;
	class PipelineDataLists;

	class MemoryObjectsList;
	class DataBufferLists;
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

		DescriptorDataLists GetDescriptorDataLists();
		RenderPassList GetRenderPassList();
		PipelineDataLists GetPipelineDataLists();

		MemoryObjectsList GetMemoryObjectsList();
		DataBufferLists GetDataBufferLists();
		ImageDataLists GetImageDataLists();

		SynchronizationDataLists GetSynchronizationDataLists();
		CommandPoolMainList GetCommandPoolMainList();

		const DeviceCore GetDeviceCore() const;
		const WindowList GetWindowList() const;
		const ShaderLists GetShaderLists() const;

		const DescriptorDataLists GetDescriptorDataLists() const;
		const RenderPassList GetRenderPassList() const;
		const PipelineDataLists GetPipelineDataLists() const;

		const MemoryObjectsList GetMemoryObjectsList() const;
		const DataBufferLists GetDataBufferLists() const;
		const ImageDataLists GetImageDataLists() const;

		const SynchronizationDataLists GetSynchronizationDataLists() const;
		const CommandPoolMainList GetCommandPoolMainList() const;

	private:
		VulkanSimplifiedInternal::DeviceMainInternal& _internal;
	};
}