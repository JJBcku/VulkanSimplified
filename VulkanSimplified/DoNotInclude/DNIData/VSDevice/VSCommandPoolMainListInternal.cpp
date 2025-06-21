#include "VSDeviceDNIpch.h"
#include "VSCommandPoolMainListInternal.h"

#include "../../../Include/VSDevice/VSCommandPoolMainListInitialCapacity.h"
#include "../../../Include/VSDevice/VSCommandPoolQFGroupListsInitialCapacities.h"

#include "VSCommandPoolQFGroupListInternal.h"

namespace VulkanSimplified
{
	CommandPoolMainListInternal::CommandPoolMainListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList,
		const CommandPoolMainListInitialCapacity& initialCapacity) : _deviceCore(deviceCore), _deviceRenderPassData(deviceRenderPassData),
		_sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList),
		_dataBufferList(dataBufferList), _windowList(windowList), _descriptorDataList(descriptorDataList), _qfGroupList(initialCapacity.qfGroupsListInitialCapacity)
	{
	}

	CommandPoolMainListInternal::~CommandPoolMainListInternal()
	{
	}

	IDObject<CommandPoolQFGroupPointer> CommandPoolMainListInternal::AddQueueFamiliesPoolGroup(uint32_t queueFamily,
		const CommandPoolQFGroupListsInitialCapacities& initialCapacities, size_t addOnReserving)
	{
		return _qfGroupList.AddObject(std::make_unique<CommandPoolQFGroupListInternal>(_deviceCore, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _dataBufferList, _windowList, _descriptorDataList, queueFamily, initialCapacities), addOnReserving);
	}

	CommandPoolQFGroupListInternal& CommandPoolMainListInternal::GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID)
	{
		return *_qfGroupList.GetObject(qfGroupID);
	}

	const CommandPoolQFGroupListInternal& CommandPoolMainListInternal::GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID) const
	{
		return *_qfGroupList.GetConstObject(qfGroupID);
	}

}