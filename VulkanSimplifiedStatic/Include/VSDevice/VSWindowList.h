#pragma once

#include "VSWindowPointer.h"

template<class T>
class IDObject;

namespace VulkanSimplifiedInternal
{
	class WindowListInternal;
}

namespace VulkanSimplified
{
	struct WindowCreationData;
	class Window;

	class WindowList
	{
	public:
		WindowList(VulkanSimplifiedInternal::WindowListInternal& ref);
		~WindowList();

		IDObject<WindowPointer> CreateWindow(const WindowCreationData& creationData, size_t addOnReserving = 0);

		Window GetWindow(IDObject<WindowPointer> windowID);

		const Window GetWindow(IDObject<WindowPointer> windowID) const;

	private:
		VulkanSimplifiedInternal::WindowListInternal& _internal;
	};
}
