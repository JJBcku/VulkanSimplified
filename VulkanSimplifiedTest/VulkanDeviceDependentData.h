#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	class WindowInternal;
}

struct VulkanDeviceDependentData
{
	IDObject<VulkanSimplifiedInternal::WindowInternal> windowID;

	VulkanDeviceDependentData();
	~VulkanDeviceDependentData();
};
