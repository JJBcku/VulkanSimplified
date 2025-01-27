#include "VSDeviceNIpch.h"
#include "VSWindowListInternal.h"

#include "../../Include/VSDevice/VSDeviceWindowListInitialCapacities.h"

namespace VulkanSimplifiedInternal
{
	WindowListInternal::WindowListInternal(const VulkanSimplified::WindowListInitialCapacities& initalCapacities) : stump(initalCapacities.stump)
	{
	}

	WindowListInternal::~WindowListInternal()
	{
	}

}