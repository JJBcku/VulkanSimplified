#include "VSDeviceNIpch.h"
#include "VSDeviceMainInternal.h"

#include "../VSInstance/VsLogicalDeviceInternalCreationData.h"

#include "../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

#include  "../VSSharedData/VSSharedDataMainListInternal.h"

namespace VulkanSimplifiedInternal
{
	DeviceMainInternal::DeviceMainInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, VkInstance instance,
		const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
		const VulkanSimplified::DeviceInitialCapacitiesList& initialCapacities) : _eventHandler(eventHandler), _sharedDataMain(sharedDataMain),
		_core(instance, creationData, physicalDeviceData),
		_windowList(_eventHandler, _core, instance, _core.GetDevicesPhysicalData().GetPhysicalDevice(), _core.GetDevice(), initialCapacities.windowList),
		_shaderLists(_core.GetDevice(), initialCapacities.shaderLists),
		_memoryObjectsList(_core.GetDevice(), _core.GetDevicesPhysicalData().GetAvailableMemoryDataList(), initialCapacities.memoryObjectsList),
		_dataBufferLists(_core, _memoryObjectsList, _core.GetDevice(), initialCapacities.dataBufferLists),
		_imageDataLists(_core, _renderPassList, _memoryObjectsList, _core.GetDevice(), initialCapacities.imageLists),
		_descriptorLists(_sharedDataMain.GetSharedDescriptorDataList(), _dataBufferLists, _core.GetDevice(), initialCapacities.descriptorLists),
		_renderPassList(_sharedDataMain.GetSharedRenderPassDataList(), _core.GetDevice(), initialCapacities.renderPassLists),
		_pipelineDataLists(sharedDataMain.GetPipelineDataList(), _descriptorLists, _shaderLists, _renderPassList, _core.GetDevice(), initialCapacities.pipelineDataLists),
		_synchroDataLists(_core.GetDevice(), initialCapacities.synchronizationLists),
		_commandPoolMainList(_core, _renderPassList, _sharedDataMain.GetSharedRenderPassDataList(), _pipelineDataLists, _synchroDataLists, _imageDataLists, _dataBufferLists,
			_windowList, _descriptorLists, initialCapacities.commandPoolMainList)
	{
	}

	DeviceMainInternal::~DeviceMainInternal()
	{
	}

	DeviceCoreInternal& DeviceMainInternal::GetDeviceCore()
	{
		return _core;
	}

	WindowListInternal& DeviceMainInternal::GetWindowList()
	{
		return _windowList;
	}

	ShaderListsInternal& DeviceMainInternal::GetShaderLists()
	{
		return _shaderLists;
	}

	MemoryObjectsListInternal& DeviceMainInternal::GetMemoryObjectsList()
	{
		return _memoryObjectsList;
	}

	DataBufferListsInternal& DeviceMainInternal::GetDataBufferLists()
	{
		return _dataBufferLists;
	}

	ImageDataListsInternal& DeviceMainInternal::GetImageDataLists()
	{
		return _imageDataLists;
	}

	DescriptorDataListsInternal& DeviceMainInternal::GetDescriptorDataLists()
	{
		return _descriptorLists;
	}

	RenderPassListInternal& DeviceMainInternal::GetRenderPassList()
	{
		return _renderPassList;
	}

	PipelineDataListsInternal& DeviceMainInternal::GetPipelineDataLists()
	{
		return _pipelineDataLists;
	}

	SynchronizationDataListsInternal& DeviceMainInternal::GetSynchronizationDataLists()
	{
		return _synchroDataLists;
	}

	CommandPoolMainListInternal& DeviceMainInternal::GetCommandPoolMainList()
	{
		return _commandPoolMainList;
	}

	const DeviceCoreInternal& DeviceMainInternal::GetDeviceCore() const
	{
		return _core;
	}

	const WindowListInternal& DeviceMainInternal::GetWindowList() const
	{
		return _windowList;
	}

	const ShaderListsInternal& DeviceMainInternal::GetShaderLists() const
	{
		return _shaderLists;
	}

	const MemoryObjectsListInternal& DeviceMainInternal::GetMemoryObjectsList() const
	{
		return _memoryObjectsList;
	}

	const DataBufferListsInternal& DeviceMainInternal::GetDataBufferLists() const
	{
		return _dataBufferLists;
	}

	const ImageDataListsInternal& DeviceMainInternal::GetImageDataLists() const
	{
		return _imageDataLists;
	}

	const DescriptorDataListsInternal& DeviceMainInternal::GetDescriptorDataLists() const
	{
		return _descriptorLists;
	}

	const RenderPassListInternal& DeviceMainInternal::GetRenderPassList() const
	{
		return _renderPassList;
	}

	const PipelineDataListsInternal& DeviceMainInternal::GetPipelineDataLists() const
	{
		return _pipelineDataLists;
	}

	const SynchronizationDataListsInternal& DeviceMainInternal::GetSynchronizationDataLists() const
	{
		return _synchroDataLists;
	}

	const CommandPoolMainListInternal& DeviceMainInternal::GetCommandPoolMainList() const
	{
		return _commandPoolMainList;
	}

}