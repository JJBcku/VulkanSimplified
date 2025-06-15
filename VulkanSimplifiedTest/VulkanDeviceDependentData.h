#pragma once

#include <CustomLists/IDObject.h>

#include <VSWindowListDef.h>
#include <VSShaderListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanDeviceDependentData
{
	IDObject<VulkanSimplified::WindowPointer> windowID;
	IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> fragmentShadersID;
	IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> vertexShadersID;

	IDObject<VulkanSimplifiedInternal::AutoCleanupSampler> sampler;

	VulkanDeviceDependentData();
	~VulkanDeviceDependentData();
};
