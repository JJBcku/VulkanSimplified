#pragma once

#include <CustomLists/IDObject.h>
#include <VSWindowPointer.h>

namespace VulkanSimplifiedInternal
{
	class WindowInternal;
	class AutoCleanupFragmentShaderModule;
	class AutoCleanupVertexShaderModule;
}

struct VulkanDeviceDependentData
{
	IDObject<VulkanSimplified::WindowPointer> windowID;
	IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> fragmentShadersID;
	IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> vertexShadersID;

	VulkanDeviceDependentData();
	~VulkanDeviceDependentData();
};
