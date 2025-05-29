#pragma once

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSDataBufferListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanTextureData
{
	VulkanSimplified::MemoryAllocationFullID textureMemoryAllocation;
	IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> textureID;
	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> textureImageView;

	VulkanTextureData();
	~VulkanTextureData();
};