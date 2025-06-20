#pragma once

#include <memory>

typedef struct VkInstance_T* VkInstance;

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplified
{
	struct LogicalDeviceInternalCreationData;
	class PhysicalDeviceDataInternal;
	class SharedDataMainListInternal;
	class SdlEventHandlerInternal;

	class DeviceCoreInternal;
	class WindowListInternal;
	class ShaderListsInternal;

	class MemoryObjectsListInternal;
	class DataBufferListsInternal;
	class ImageDataListsInternal;

	class DescriptorDataListsInternal;
	class RenderPassListInternal;
	class PipelineDataListsInternal;

	class SynchronizationDataListsInternal;
	class CommandPoolMainListInternal;

	class DeviceMainInternal
	{
	public:
		DeviceMainInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, VkInstance instance,
			const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
			const DeviceInitialCapacitiesList& initialCapacities);
		~DeviceMainInternal();

		DeviceCoreInternal& GetDeviceCore();
		WindowListInternal& GetWindowList();
		ShaderListsInternal& GetShaderLists();
		RenderPassListInternal& GetRenderPassList();

		MemoryObjectsListInternal& GetMemoryObjectsList();
		DataBufferListsInternal& GetDataBufferLists();
		ImageDataListsInternal& GetImageDataLists();

		DescriptorDataListsInternal& GetDescriptorDataLists();
		PipelineDataListsInternal& GetPipelineDataLists();
		SynchronizationDataListsInternal& GetSynchronizationDataLists();

		CommandPoolMainListInternal& GetCommandPoolMainList();

		const DeviceCoreInternal& GetDeviceCore() const;
		const WindowListInternal& GetWindowList() const;
		const ShaderListsInternal& GetShaderLists() const;
		const RenderPassListInternal& GetRenderPassList() const;

		const MemoryObjectsListInternal& GetMemoryObjectsList() const;
		const DataBufferListsInternal& GetDataBufferLists() const;
		const ImageDataListsInternal& GetImageDataLists() const;

		const DescriptorDataListsInternal& GetDescriptorDataLists() const;
		const PipelineDataListsInternal& GetPipelineDataLists() const;
		const SynchronizationDataListsInternal& GetSynchronizationDataLists() const;

		const CommandPoolMainListInternal& GetCommandPoolMainList() const;

	private:
		SdlEventHandlerInternal& _eventHandler;
		const SharedDataMainListInternal& _sharedDataMain;

		std::unique_ptr<DeviceCoreInternal> _core;
		std::unique_ptr<WindowListInternal> _windowList;
		std::unique_ptr<ShaderListsInternal> _shaderLists;
		std::unique_ptr<RenderPassListInternal> _renderPassList;

		std::unique_ptr<MemoryObjectsListInternal> _memoryObjectsList;
		std::unique_ptr<DataBufferListsInternal> _dataBufferLists;
		std::unique_ptr<ImageDataListsInternal> _imageDataLists;

		std::unique_ptr<DescriptorDataListsInternal> _descriptorLists;
		std::unique_ptr<PipelineDataListsInternal> _pipelineDataLists;
		std::unique_ptr<SynchronizationDataListsInternal> _synchroDataLists;

		std::unique_ptr<CommandPoolMainListInternal> _commandPoolMainList;
	};
}