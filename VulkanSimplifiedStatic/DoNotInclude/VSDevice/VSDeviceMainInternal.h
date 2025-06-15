#pragma once

#include "VSDeviceCoreInternal.h"
#include "VSWindowListInternal.h"
#include "VSShaderListsInternal.h"

#include "VSDescriptorDataListsInternal.h"
#include "VSRenderPassDataListInternal.h"
#include "VSPipelineDataListsInternal.h"

#include "VSMemoryObjectsListInternal.h"
#include "VSDataBufferListsInternal.h"
#include "VSImageDataListsInternal.h"

#include "VSSynchronizationDataListsInternal.h"
#include "VSCommandPoolMainListInternal.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData;
	class PhysicalDeviceDataInternal;
	class SharedDataMainListInternal;
	class SdlEventHandlerInternal;

	class DeviceMainInternal
	{
	public:
		DeviceMainInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, VkInstance instance,
			const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
			const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities);
		~DeviceMainInternal();

		DeviceCoreInternal& GetDeviceCore();
		WindowListInternal& GetWindowList();
		ShaderListsInternal& GetShaderLists();

		MemoryObjectsListInternal& GetMemoryObjectsList();
		DataBufferListsInternal& GetDataBufferLists();
		ImageDataListsInternal& GetImageDataLists();

		DescriptorDataListsInternal& GetDescriptorDataLists();
		RenderPassListInternal& GetRenderPassList();
		PipelineDataListsInternal& GetPipelineDataLists();

		SynchronizationDataListsInternal& GetSynchronizationDataLists();
		CommandPoolMainListInternal& GetCommandPoolMainList();

		const DeviceCoreInternal& GetDeviceCore() const;
		const WindowListInternal& GetWindowList() const;
		const ShaderListsInternal& GetShaderLists() const;

		const MemoryObjectsListInternal& GetMemoryObjectsList() const;
		const DataBufferListsInternal& GetDataBufferLists() const;
		const ImageDataListsInternal& GetImageDataLists() const;

		const DescriptorDataListsInternal& GetDescriptorDataLists() const;
		const RenderPassListInternal& GetRenderPassList() const;
		const PipelineDataListsInternal& GetPipelineDataLists() const;

		const SynchronizationDataListsInternal& GetSynchronizationDataLists() const;
		const CommandPoolMainListInternal& GetCommandPoolMainList() const;

	private:
		SdlEventHandlerInternal& _eventHandler;
		const SharedDataMainListInternal& _sharedDataMain;

		DeviceCoreInternal _core;
		WindowListInternal _windowList;
		ShaderListsInternal _shaderLists;

		MemoryObjectsListInternal _memoryObjectsList;
		DataBufferListsInternal _dataBufferLists;
		ImageDataListsInternal _imageDataLists;

		DescriptorDataListsInternal _descriptorLists;
		RenderPassListInternal _renderPassList;
		PipelineDataListsInternal _pipelineDataLists;

		SynchronizationDataListsInternal _synchroDataLists;
		CommandPoolMainListInternal _commandPoolMainList;
	};
}