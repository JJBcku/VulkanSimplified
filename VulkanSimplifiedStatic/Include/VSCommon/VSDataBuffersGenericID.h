#pragma once

#include <CustomLists/IDObject.h>

#include "../VSDevice/VSDataBufferListsDef.h"

#include <stdint.h>

namespace VulkanSimplified
{
	enum class DataBuffersIDType : uint64_t
	{
		UNKNOWN = 0,
		VERTEX = 1,
		STAGING = 2,
		INDEX = 4,
		UNIFORM = 8,
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

		struct
		{
			DataBuffersIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> ID;
		} indexID;

		struct
		{
			DataBuffersIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> ID;
		} uniformID;

		DataBuffersGenericID();
		DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> ID);
		DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> ID);
		DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> ID);
		DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> ID);
	};
}