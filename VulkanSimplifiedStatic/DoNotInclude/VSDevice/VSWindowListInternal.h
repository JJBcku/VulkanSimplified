#pragma once

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplified
{
	struct WindowListInitialCapacities;
	struct WindowCreationData;
}

namespace VulkanSimplifiedInternal
{
	class WindowInternal;

	class WindowListInternal
	{
	public:
		WindowListInternal(VkInstance instance, VkDevice device, const VulkanSimplified::WindowListInitialCapacities& initalCapacities);
		~WindowListInternal();

		IDObject<WindowInternal> CreateWindow(const VulkanSimplified::WindowCreationData& creationData, size_t addOnReserving);

	private:
		VkInstance _instance;
		VkDevice _device;

		UnsortedIDVector<WindowInternal> _windowList;
	};
}