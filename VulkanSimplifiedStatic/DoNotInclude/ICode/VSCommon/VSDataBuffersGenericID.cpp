#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSDataBuffersGenericID.h"

namespace VulkanSimplified
{
	DataBuffersGenericID::DataBuffersGenericID()
	{
		type = DataBuffersIDType::UNKNOWN;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupVertexBuffer> ID)
	{
		vertexID.type = DataBuffersIDType::VERTEX;
		vertexID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupStagingBuffer> ID)
	{
		stagingID.type = DataBuffersIDType::STAGING;
		stagingID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupIndexBuffer> ID)
	{
		indexID.type = DataBuffersIDType::INDEX;
		indexID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupUniformBuffer> ID)
	{
		uniformID.type = DataBuffersIDType::UNIFORM;
		uniformID.ID = ID;
	}
}