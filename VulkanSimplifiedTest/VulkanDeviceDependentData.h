#pragma once

#include <CustomLists/IDObject.h>
#include <VSWindowPointer.h>

namespace VulkanSimplifiedInternal
{
	class WindowInternal;
}

struct VulkanDeviceDependentData
{
	IDObject<VulkanSimplified::WindowPointer> windowID;

	VulkanDeviceDependentData();
	~VulkanDeviceDependentData();
};
