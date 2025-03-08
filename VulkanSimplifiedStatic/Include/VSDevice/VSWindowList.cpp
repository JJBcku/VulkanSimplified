#include "VSDeviceIpch.h"
#include "VSWindowList.h"

#include "VSWindow.h"

#include "../../DoNotInclude/VSDevice/VSWindowListInternal.h"
#include "../../DoNotInclude/VSDevice/VSWindowInternal.h"

#include <CustomLists/IDObject.h>

namespace VulkanSimplified
{
	WindowList::WindowList(VulkanSimplifiedInternal::WindowListInternal& ref) : _internal(ref)
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