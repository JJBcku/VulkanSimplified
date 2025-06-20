#pragma once

#include <CustomLists/IDObject.h>

#include <VSWindowListDef.h>
#include <VSShaderListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanDeviceDependentData
{
	IDObject<VulkanSimplified::WindowPointer> windowID;
	IDObject<VulkanSimplified::AutoCleanupFragmentShaderModule> fragmentShadersID;
	IDObject<VulkanSimplified::AutoCleanupVertexShaderModule> vertexShadersID;

	IDObject<VulkanSimplified::AutoCleanupSampler> sampler;

	VulkanDeviceDependentData();
	~VulkanDeviceDependentData();
};
