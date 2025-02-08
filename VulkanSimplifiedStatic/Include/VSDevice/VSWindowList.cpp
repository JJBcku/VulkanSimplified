#include "VSDeviceIpch.h"
#include "VSWindowList.h"

#include "../../DoNotInclude/VSDevice/VSWindowListInternal.h"

#include <CustomLists/IDObject.h>

namespace VulkanSimplified
{
	WindowList::WindowList(VulkanSimplifiedInternal::WindowListInternal& ref) : _internal(ref)
	{
	}

	WindowList::~WindowList()
	{
	}

	IDObject<VulkanSimplifiedInternal::WindowInternal> WindowList::CreateWindow(const WindowCreationData& creationData, size_t addOnReserving)
	{
		return _internal.CreateWindow(creationData, addOnReserving);
	}

}