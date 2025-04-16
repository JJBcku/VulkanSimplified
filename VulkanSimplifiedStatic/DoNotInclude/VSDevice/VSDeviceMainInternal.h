#pragma once

#include "VSDeviceCoreInternal.h"
#include "VSWindowListInternal.h"
#include "VSShaderListsInternal.h"
#include "VSRenderPassDataListInternal.h"
#include "VSPipelineDataListsInternal.h"

#include "VSDescriptorDataListInternal.h"

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

		const DeviceCoreInternal& GetDeviceCore() const;
		const WindowListInternal& GetWindowList() const;
		const ShaderListsInternal& GetShaderLists() const;

		const DescriptorDataListInternal& GetDescriptorDataLists() const;
		const RenderPassListInternal& GetRenderPassList() const;
		const PipelineDataListsInternal& GetPipelineDataLists() const;

	private:
		const SharedDataMainListInternal& _sharedDataMain;

		DeviceCoreInternal _core;
		WindowListInternal _windowList;
		ShaderListsInternal _shaderLists;

		RenderPassListInternal _renderPassList;
		PipelineDataListsInternal _pipelineDataLists;

		DescriptorDataListInternal _descriptorLists;
	};
}