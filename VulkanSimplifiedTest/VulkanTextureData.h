#pragma once

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSDataBufferListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanTextureData
{
	VulkanSimplified::MemoryAllocationFullID textureMemoryAllocation;
	IDObject<VulkanSimplified::AutoCleanup2DTexture> textureID;
	IDObject<VulkanSimplified::AutoCleanupImageView> textureImageView;

	VulkanTextureData();
	~VulkanTextureData();
};