#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSWindowList.h"

#include "../../../Include/VSDevice/VSWindow.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSWindowListInternal.h"
#include "../../../DoNotInclude/DNIData/VSDevice/VSWindowInternal.h"

#include <CustomLists/IDObject.h>

namespace VulkanSimplified
{
	WindowList::WindowList(WindowListInternal& ref) : _internal(ref)
	{
	}

	WindowList::~WindowList()
	{
	}

	IDObject<WindowPointer> WindowList::CreateWindow(const WindowCreationData& creationData, size_t addOnReserving)
	{
		return _internal.CreateWindow(creationData, addOnReserving);
	}

	Window WindowList::GetWindow(IDObject<WindowPointer> windowID)
	{
		return _internal.GetWindow(windowID);
	}

	const Window WindowList::GetWindow(IDObject<WindowPointer> windowID) const
	{
		return _internal.GetWindow(windowID);
	}

}