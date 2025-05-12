#include "VSCommonIpch.h"
#include "VSDataBuffersGenericID.h"

namespace VulkanSimplified
{
	DataBuffersGenericID::DataBuffersGenericID()
	{
		type = DataBuffersIDType::UNKNOWN;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> ID)
	{
		vertexID.type = DataBuffersIDType::VERTEX;
		vertexID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> ID)
	{
		stagingID.type = DataBuffersIDType::STAGING;
		stagingID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> ID)
	{
		indexID.type = DataBuffersIDType::INDEX;
		indexID.ID = ID;
	}
}