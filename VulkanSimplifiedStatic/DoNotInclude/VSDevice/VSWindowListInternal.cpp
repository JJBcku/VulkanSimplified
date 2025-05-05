#include "VSDeviceNIpch.h"
#include "VSWindowListInternal.h"

#include "../../Include/VSDevice/VSWindowListInitialCapacities.h"
#include "../../Include/VSDevice/VSWindowCreationData.h"

#include "VSWindowInternal.h"

namespace VulkanSimplifiedInternal
{
	WindowListInternal::WindowListInternal(SdlEventHandlerInternal& eventHandler, DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
		const VulkanSimplified::WindowListInitialCapacities& initalCapacities) : _eventHandler(eventHandler), _core(core), _instance(instance), _physicalDevice(physicalDevice),
		_device(device), _windowList(initalCapacities.windowListInitialCapacity)
	{
	}

	WindowListInternal::~WindowListInternal()
	{
	}

	IDObject<VulkanSimplified::WindowPointer> WindowListInternal::CreateWindow(const VulkanSimplified::WindowCreationData& creationData, size_t addOnReserving)
	{
		return _windowList.AddObject(std::make_unique<WindowInternal>(_eventHandler, _core, _instance, _physicalDevice, _device, creationData), addOnReserving);
	}

	WindowInternal& WindowListInternal::GetWindow(IDObject<VulkanSimplified::WindowPointer> windowID)
	{
		return *_windowList.GetObject(windowID);
	}

	const WindowInternal& WindowListInternal::GetWindow(IDObject<VulkanSimplified::WindowPointer> windowID) const
	{
		return *_windowList.GetConstObject(windowID);
	}

}