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
	class SynchronizationDataListsInternal;
	class WindowInternal;
	class SdlEventHandlerInternal;

	class WindowListInternal
	{
	public:
		WindowListInternal(SdlEventHandlerInternal& eventHandler, DeviceCoreInternal& core, SynchronizationDataListsInternal& synchroList,
			VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device, const WindowListInitialCapacities& initalCapacities);
		~WindowListInternal();

		IDObject<WindowPointer> CreateWindow(const WindowCreationData& creationData, size_t addOnReserving);

		WindowInternal& GetWindow(IDObject<WindowPointer> windowID);

		const WindowInternal& GetWindow(IDObject<WindowPointer> windowID) const;

	private:
		SdlEventHandlerInternal& _eventHandler;
		DeviceCoreInternal& _core;
		SynchronizationDataListsInternal& _synchroList;

		VkInstance _instance;
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		UnsortedIDVector<WindowPointer> _windowList;
	};
}