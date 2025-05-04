#pragma once

#include "VSDeviceCoreInternal.h"
#include "VSWindowListInternal.h"
#include "VSShaderListsInternal.h"

#include "VSDescriptorDataListInternal.h"
#include "VSRenderPassDataListInternal.h"
#include "VSPipelineDataListsInternal.h"

#include "VSMemoryObjectsListInternal.h"
#include "VSImageDataListsInternal.h"

#include "VSSynchronizationDataListsInternal.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList;
}

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData;
	class PhysicalDeviceDataInternal;
	class SharedDataMainListInternal;

	class DeviceMainInternal
	{
	public:
		DeviceMainInternal(const SharedDataMainListInternal& sharedDataMain, VkInstance instance, const LogicalDeviceInternalCreationData& creationData,
			const PhysicalDeviceDataInternal& physicalDeviceData, const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities);
		~DeviceMainInternal();

		DeviceCoreInternal& GetDeviceCore();
		WindowListInternal& GetWindowList();
		ShaderListsInternal& GetShaderLists();

		DescriptorDataListInternal& GetDescriptorDataLists();
		RenderPassListInternal& GetRenderPassList();
		PipelineDataListsInternal& GetPipelineDataLists();

		MemoryObjectsListInternal& GetMemoryObjectsList();
		ImageDataListsInternal& GetImageDataLists();

		SynchronizationDataListsInternal& GetSynchronizationDataLists();

		const DeviceCoreInternal& GetDeviceCore() const;
		const WindowListInternal& GetWindowList() const;
		const ShaderListsInternal& GetShaderLists() const;

		const DescriptorDataListInternal& GetDescriptorDataLists() const;
		const RenderPassListInternal& GetRenderPassList() const;
		const PipelineDataListsInternal& GetPipelineDataLists() const;

		const MemoryObjectsListInternal& GetMemoryObjectsList() const;
		const ImageDataListsInternal& GetImageDataLists() const;

		const SynchronizationDataListsInternal& GetSynchronizationDataLists() const;

	private:
		const SharedDataMainListInternal& _sharedDataMain;

		DeviceCoreInternal _core;
		WindowListInternal _windowList;
		ShaderListsInternal _shaderLists;

		DescriptorDataListInternal _descriptorLists;
		RenderPassListInternal _renderPassList;
		PipelineDataListsInternal _pipelineDataLists;

		MemoryObjectsListInternal _memoryObjectsList;
		ImageDataListsInternal _imageDataLists;

		SynchronizationDataListsInternal _synchroDataLists;
	};
}