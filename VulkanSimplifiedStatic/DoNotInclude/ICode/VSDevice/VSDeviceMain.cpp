#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDeviceMain.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSDeviceMainInternal.h"

#include "../../../Include/VSDevice/VSDeviceCore.h"
#include "../../../Include/VSDevice/VSWindowList.h"
#include "../../../Include/VSDevice/VSShaderLists.h"

#include "../../../Include/VSDevice/VSDescriptorDataLists.h"
#include "../../../Include/VSDevice/VSRenderPassDataList.h"
#include "../../../Include/VSDevice/VSPipelineDataLists.h"

#include "../../../Include/VSDevice/VSMemoryObjectsList.h"
#include "../../../Include/VSDevice/VSDataBufferLists.h"
#include "../../../Include/VSDevice/VSImageDataLists.h"

#include "../../../Include/VSDevice/VSSynchronizationDataLists.h"
#include "../../../Include/VSDevice/VSCommandPoolMainList.h"

namespace VulkanSimplified
{
	DeviceMain::DeviceMain(VulkanSimplifiedInternal::DeviceMainInternal& ref) : _internal(ref)
	{
	}

	DeviceMain::~DeviceMain()
	{
	}

	DeviceCore DeviceMain::GetDeviceCore()
	{
		return _internal.GetDeviceCore();
	}

	WindowList DeviceMain::GetWindowList()
	{
		return _internal.GetWindowList();
	}

	ShaderLists DeviceMain::GetShaderLists()
	{
		return _internal.GetShaderLists();
	}

	MemoryObjectsList DeviceMain::GetMemoryObjectsList()
	{
		return _internal.GetMemoryObjectsList();
	}

	DataBufferLists DeviceMain::GetDataBufferLists()
	{
		return _internal.GetDataBufferLists();
	}

	ImageDataLists DeviceMain::GetImageDataLists()
	{
		return _internal.GetImageDataLists();
	}

	DescriptorDataLists DeviceMain::GetDescriptorDataLists()
	{
		return _internal.GetDescriptorDataLists();
	}

	RenderPassList DeviceMain::GetRenderPassList()
	{
		return _internal.GetRenderPassList();
	}

	PipelineDataLists DeviceMain::GetPipelineDataLists()
	{
		return _internal.GetPipelineDataLists();
	}

	SynchronizationDataLists DeviceMain::GetSynchronizationDataLists()
	{
		return _internal.GetSynchronizationDataLists();
	}

	CommandPoolMainList DeviceMain::GetCommandPoolMainList()
	{
		return _internal.GetCommandPoolMainList();
	}

	const DeviceCore DeviceMain::GetDeviceCore() const
	{
		return _internal.GetDeviceCore();
	}

	const WindowList DeviceMain::GetWindowList() const
	{
		return _internal.GetWindowList();
	}

	const ShaderLists DeviceMain::GetShaderLists() const
	{
		return _internal.GetShaderLists();
	}

	const MemoryObjectsList DeviceMain::GetMemoryObjectsList() const
	{
		return _internal.GetMemoryObjectsList();
	}

	const DataBufferLists DeviceMain::GetDataBufferLists() const
	{
		return _internal.GetDataBufferLists();
	}

	const ImageDataLists DeviceMain::GetImageDataLists() const
	{
		return _internal.GetImageDataLists();
	}

	const DescriptorDataLists DeviceMain::GetDescriptorDataLists() const
	{
		return _internal.GetDescriptorDataLists();
	}

	const RenderPassList DeviceMain::GetRenderPassList() const
	{
		return _internal.GetRenderPassList();
	}

	const PipelineDataLists DeviceMain::GetPipelineDataLists() const
	{
		return _internal.GetPipelineDataLists();
	}

	const SynchronizationDataLists DeviceMain::GetSynchronizationDataLists() const
	{
		return _internal.GetSynchronizationDataLists();
	}

	const CommandPoolMainList DeviceMain::GetCommandPoolMainList() const
	{
		return _internal.GetCommandPoolMainList();
	}

}