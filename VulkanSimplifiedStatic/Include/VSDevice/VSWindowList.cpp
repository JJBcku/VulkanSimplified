#include "VSDeviceIpch.h"
#include "VSWindowList.h"

#include "../../DoNotInclude/VSDevice/VSWindowListInternal.h"

namespace VulkanSimplified
{
	WindowList::WindowList(VulkanSimplifiedInternal::WindowListInternal& ref) : _internal(ref)
	{
	}

	WindowList::~WindowList()
	{
	}

}