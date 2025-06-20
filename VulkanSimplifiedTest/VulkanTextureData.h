#pragma once

#include <CustomLists/IDObject.h>

#include <VSMemoryAllocationFullID.h>
#include <VSDataBufferListsDef.h>
#include <VSImageDataListsDef.h>

struct VulkanTextureData
{
	VS::MemoryAllocationFullID textureMemoryAllocation;
	IDObject<VS::AutoCleanup2DTexture> textureID;
	IDObject<VS::AutoCleanupImageView> textureImageView;

	VulkanTextureData();
	~VulkanTextureData();
};