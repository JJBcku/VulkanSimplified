#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../../Include/VSDevice/VSWindowListDef.h"

typedef struct VkInstance_T* VkInstance;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkDevice_T* VkDevice;

namespace VulkanSimplified
{
	struct WindowListInitialCapacities;
	struct WindowCreationData;
}

namespace VulkanSimplified
{
	class DeviceCoreInternal;
	class WindowInternal;
	class SdlEventHandlerInternal;

	class WindowListInternal
	{
	public:
		WindowListInternal(SdlEventHandlerInternal& eventHandler, DeviceCoreInternal& core, VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
			const WindowListInitialCapacities& initalCapacities);
		~WindowListInternal();

		IDObject<WindowPointer> CreateWindow(const WindowCreationData& creationData, size_t addOnReserving);

		WindowInternal& GetWindow(IDObject<WindowPointer> windowID);

		const WindowInternal& GetWindow(IDObject<WindowPointer> windowID) const;

	private:
		SdlEventHandlerInternal& _eventHandler;
		DeviceCoreInternal& _core;

		VkInstance _instance;
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		UnsortedIDVector<WindowPointer> _windowList;
	};
}