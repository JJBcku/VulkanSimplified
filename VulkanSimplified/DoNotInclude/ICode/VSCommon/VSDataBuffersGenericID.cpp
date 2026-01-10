#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSDataBuffersGenericID.h"

namespace VulkanSimplified
{
	DataBuffersGenericID::DataBuffersGenericID() noexcept
	{
		type = DataBuffersIDType::UNKNOWN;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupVertexBuffer> ID) noexcept
	{
		vertexID.type = DataBuffersIDType::VERTEX;
		vertexID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupStagingBuffer> ID) noexcept
	{
		stagingID.type = DataBuffersIDType::STAGING;
		stagingID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupIndexBuffer> ID) noexcept
	{
		indexID.type = DataBuffersIDType::INDEX;
		indexID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(IDObject<AutoCleanupUniformBuffer> ID) noexcept
	{
		uniformID.type = DataBuffersIDType::UNIFORM;
		uniformID.ID = ID;
	}

	DataBuffersGenericID::DataBuffersGenericID(const DataBuffersGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DataBuffersGenericID));
	}

	DataBuffersGenericID::DataBuffersGenericID(DataBuffersGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DataBuffersGenericID));

		rhs.type = DataBuffersIDType::UNKNOWN;
	}

	DataBuffersGenericID::~DataBuffersGenericID()
	{
	}

	DataBuffersGenericID& DataBuffersGenericID::operator=(const DataBuffersGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DataBuffersGenericID));
		return *this;
	}

	DataBuffersGenericID& DataBuffersGenericID::operator=(DataBuffersGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DataBuffersGenericID));
		rhs.type = DataBuffersIDType::UNKNOWN;
		return *this;
	}

}