#include "VSDeviceNIpch.h"
#include "VSCommandPoolMainListInternal.h"

#include "../../Include/VSDevice/VSCommandPoolMainListInitialCapacity.h"
#include "../../Include/VSDevice/VSCommandPoolQFGroupListsInitialCapacities.h"

#include "VSCommandPoolQFGroupListInternal.h"

namespace VulkanSimplifiedInternal
{
	CommandPoolMainListInternal::CommandPoolMainListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList,
		const VulkanSimplified::CommandPoolMainListInitialCapacity& initialCapacity) : _deviceCore(deviceCore), _deviceRenderPassData(deviceRenderPassData),
		_sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList),
		_dataBufferList(dataBufferList), _windowList(windowList), _descriptorDataList(descriptorDataList), _qfGroupList(initialCapacity.qfGroupsListInitialCapacity)
	{
	}

	CommandPoolMainListInternal::~CommandPoolMainListInternal()
	{
	}

	IDObject<VulkanSimplified::CommandPoolQFGroupPointer> CommandPoolMainListInternal::AddQueueFamiliesPoolGroup(uint32_t queueFamily,
		const VulkanSimplified::CommandPoolQFGroupListsInitialCapacities& initialCapacities, size_t addOnReserving)
	{
		return _qfGroupList.AddObject(std::make_unique<CommandPoolQFGroupListInternal>(_deviceCore, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _dataBufferList, _windowList, _descriptorDataList, queueFamily, initialCapacities), addOnReserving);
	}

	CommandPoolQFGroupListInternal& CommandPoolMainListInternal::GetQueueFamiliesPoolGroup(IDObject<VulkanSimplified::CommandPoolQFGroupPointer> qfGroupID)
	{
		return *_qfGroupList.GetObject(qfGroupID);
	}

	const CommandPoolQFGroupListInternal& CommandPoolMainListInternal::GetQueueFamiliesPoolGroup(IDObject<VulkanSimplified::CommandPoolQFGroupPointer> qfGroupID) const
	{
		return *_qfGroupList.GetConstObject(qfGroupID);
	}

}