#include "VSDeviceDNIpch.h"
#include "VSDeviceMainInternal.h"

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

#include "../VSInstance/VSLogicalDeviceInternalCreationData.h"

#include "../../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

#include  "../VSSharedData/VSSharedDataMainListInternal.h"

namespace VulkanSimplified
{
	DeviceMainInternal::DeviceMainInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, VkInstance instance,
		const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData,
		const DeviceInitialCapacitiesList& initialCapacities) : _eventHandler(eventHandler), _sharedDataMain(sharedDataMain)
	{
		_core = std::make_unique<DeviceCoreInternal>(instance, creationData, physicalDeviceData);
		_shaderLists = std::make_unique<ShaderListsInternal>(_core->GetDevice(), initialCapacities.shaderLists);
		_renderPassList = std::make_unique<RenderPassListInternal>(_sharedDataMain.GetSharedRenderPassDataList(), _core->GetDevice(), initialCapacities.renderPassLists);

		_memoryObjectsList = std::make_unique<MemoryObjectsListInternal>(_core->GetDevice(), _core->GetDevicesPhysicalData().GetAvailableMemoryDataList(),
			initialCapacities.memoryObjectsList);
		_dataBufferLists = std::make_unique<DataBufferListsInternal>(*_core, *_memoryObjectsList, _core->GetDevice(), initialCapacities.dataBufferLists);
		_imageDataLists = std::make_unique<ImageDataListsInternal>(*_core, *_renderPassList, *_memoryObjectsList, _core->GetDevice(), initialCapacities.imageLists);

		_descriptorLists = std::make_unique<DescriptorDataListsInternal>(_sharedDataMain.GetSharedDescriptorDataList(), *_dataBufferLists, *_imageDataLists, _core->GetDevice(),
			initialCapacities.descriptorLists);
		_pipelineDataLists = std::make_unique<PipelineDataListsInternal>(sharedDataMain.GetPipelineDataList(), *_descriptorLists, *_shaderLists, *_renderPassList, _core->GetDevice(),
			initialCapacities.pipelineDataLists);
		_synchroDataLists = std::make_unique<SynchronizationDataListsInternal>(_core->GetDevice(), initialCapacities.synchronizationLists);

		_windowList = std::make_unique<WindowListInternal>(_eventHandler, *_core, *_synchroDataLists, instance, _core->GetDevicesPhysicalData().GetPhysicalDevice(), _core->GetDevice(),
			initialCapacities.windowList);
		_commandPoolMainList = std::make_unique<CommandPoolMainListInternal>(*_core, *_renderPassList, _sharedDataMain.GetSharedRenderPassDataList(), *_pipelineDataLists,
			*_synchroDataLists, *_imageDataLists, *_dataBufferLists, *_windowList, *_descriptorLists, initialCapacities.commandPoolMainList);
	}

	DeviceMainInternal::~DeviceMainInternal()
	{
	}

	DeviceCoreInternal& DeviceMainInternal::GetDeviceCore()
	{
		return *_core;
	}

	WindowListInternal& DeviceMainInternal::GetWindowList()
	{
		return *_windowList;
	}

	RenderPassListInternal& DeviceMainInternal::GetRenderPassList()
	{
		return *_renderPassList;
	}

	ShaderListsInternal& DeviceMainInternal::GetShaderLists()
	{
		return *_shaderLists;
	}

	MemoryObjectsListInternal& DeviceMainInternal::GetMemoryObjectsList()
	{
		return *_memoryObjectsList;
	}

	DataBufferListsInternal& DeviceMainInternal::GetDataBufferLists()
	{
		return *_dataBufferLists;
	}

	ImageDataListsInternal& DeviceMainInternal::GetImageDataLists()
	{
		return *_imageDataLists;
	}

	DescriptorDataListsInternal& DeviceMainInternal::GetDescriptorDataLists()
	{
		return *_descriptorLists;
	}

	PipelineDataListsInternal& DeviceMainInternal::GetPipelineDataLists()
	{
		return *_pipelineDataLists;
	}

	SynchronizationDataListsInternal& DeviceMainInternal::GetSynchronizationDataLists()
	{
		return *_synchroDataLists;
	}

	CommandPoolMainListInternal& DeviceMainInternal::GetCommandPoolMainList()
	{
		return *_commandPoolMainList;
	}

	const DeviceCoreInternal& DeviceMainInternal::GetDeviceCore() const
	{
		return *_core;
	}

	const WindowListInternal& DeviceMainInternal::GetWindowList() const
	{
		return *_windowList;
	}

	const ShaderListsInternal& DeviceMainInternal::GetShaderLists() const
	{
		return *_shaderLists;
	}

	const RenderPassListInternal& DeviceMainInternal::GetRenderPassList() const
	{
		return *_renderPassList;
	}

	const MemoryObjectsListInternal& DeviceMainInternal::GetMemoryObjectsList() const
	{
		return *_memoryObjectsList;
	}

	const DataBufferListsInternal& DeviceMainInternal::GetDataBufferLists() const
	{
		return *_dataBufferLists;
	}

	const ImageDataListsInternal& DeviceMainInternal::GetImageDataLists() const
	{
		return *_imageDataLists;
	}

	const DescriptorDataListsInternal& DeviceMainInternal::GetDescriptorDataLists() const
	{
		return *_descriptorLists;
	}

	const PipelineDataListsInternal& DeviceMainInternal::GetPipelineDataLists() const
	{
		return *_pipelineDataLists;
	}

	const SynchronizationDataListsInternal& DeviceMainInternal::GetSynchronizationDataLists() const
	{
		return *_synchroDataLists;
	}

	const CommandPoolMainListInternal& DeviceMainInternal::GetCommandPoolMainList() const
	{
		return *_commandPoolMainList;
	}

}