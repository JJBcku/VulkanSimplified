#pragma once

#include <CustomLists/IDObject.h>

#include <VSWindowListDef.h>
#include <VSShaderListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanDeviceDependentData
{
	IDObject<VS::WindowPointer> windowID;
	IDObject<VS::AutoCleanupFragmentShaderModule> fragmentShadersID;
	IDObject<VS::AutoCleanupVertexShaderModule> vertexShadersID;

	IDObject<VS::AutoCleanupSampler> sampler;

	VulkanDeviceDependentData();
	~VulkanDeviceDependentData();
};
