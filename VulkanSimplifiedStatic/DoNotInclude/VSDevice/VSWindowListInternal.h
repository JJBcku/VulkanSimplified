#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSDevice/VSWindowListDef.h"

namespace VulkanSimplified
{
	struct WindowListInitialCapacities;
	struct WindowCreationData;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
	class WindowInternal;
	class SdlEventHandlerInternal;

	class WindowListInternal
	{
	public:
		WindowListInternal(SdlEventHandlerInternal& eventHandler, DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
			const VulkanSimplified::WindowListInitialCapacities& initalCapacities);
		~WindowListInternal();

		IDObject<VulkanSimplified::WindowPointer> CreateWindow(const VulkanSimplified::WindowCreationData& creationData, size_t addOnReserving);

		WindowInternal& GetWindow(IDObject<VulkanSimplified::WindowPointer> windowID);

		const WindowInternal& GetWindow(IDObject<VulkanSimplified::WindowPointer> windowID) const;

	private:
		SdlEventHandlerInternal& _eventHandler;
		DeviceCoreInternal& _core;

		VkInstance _instance;
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		UnsortedIDVector<VulkanSimplified::WindowPointer> _windowList;
	};
}