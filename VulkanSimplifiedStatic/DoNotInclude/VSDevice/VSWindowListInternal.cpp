#include "VSDeviceNIpch.h"
#include "VSWindowListInternal.h"

#include "../../Include/VSDevice/VSDeviceWindowListInitialCapacities.h"
#include "../../Include/VSDevice/VSWindowCreationData.h"

#include "VSWindowInternal.h"

namespace VulkanSimplifiedInternal
{
	WindowListInternal::WindowListInternal(VkInstance instance, VkDevice device, const VulkanSimplified::WindowListInitialCapacities& initalCapacities) :
		_instance(instance), _device(device), _windowList(initalCapacities.windowListInitialCapacity)
	{
	}

	WindowListInternal::~WindowListInternal()
	{
	}

	IDObject<WindowInternal> WindowListInternal::CreateWindow(const VulkanSimplified::WindowCreationData& creationData, size_t addOnReserving)
	{
		return _windowList.AddObject(WindowInternal(_instance, _device, creationData), addOnReserving);
	}

}