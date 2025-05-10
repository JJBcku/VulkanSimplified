#pragma once

#include <CustomLists/IDObject.h>

#include "../VSDevice/VSDataBufferListsDef.h"

namespace VulkanSimplified
{
	enum class DataBuffersIDType : uint64_t
	{
		UNKNOWN = 0,
		VERTEX = 1,
		STAGING = 2,
	};

	union DataBuffersGenericID
	{
		DataBuffersIDType type;

		struct
		{
			DataBuffersIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> ID;
		} vertexID;

		struct
		{
			DataBuffersIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> ID;
		} stagingID;

		DataBuffersGenericID();
		DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> ID);
		DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> ID);
	};
}