#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSDataBuffersGenericID.h"

namespace VulkanSimplified
{
	DataBuffersGenericID::DataBuffersGenericID() noexcept
	{
		type = DataBuffersIDType::UNKNOWN;
	}

	DataBuffersGenericID::DataBuffersGenericID(const IDObject<AutoCleanupVertexBuffer>& ID) noexcept : vertexID(ID)
	{
	}

	DataBuffersGenericID::DataBuffersGenericID(const IDObject<AutoCleanupStagingBuffer>& ID) noexcept : stagingID(ID)
	{
	}

	DataBuffersGenericID::DataBuffersGenericID(const IDObject<AutoCleanupIndexBuffer>& ID) noexcept : indexID(ID)
	{
	}

	DataBuffersGenericID::DataBuffersGenericID(const IDObject<AutoCleanupUniformBuffer>& ID) noexcept : uniformID(ID)
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

	DataBuffersGenericID::DataBuffersVertexID::DataBuffersVertexID(const IDObject<AutoCleanupVertexBuffer>& ID) noexcept : ID(ID)
	{
		type = DataBuffersIDType::VERTEX;
	}

	DataBuffersGenericID::DataBuffersStagingID::DataBuffersStagingID(const IDObject<AutoCleanupStagingBuffer>& ID) noexcept : ID(ID)
	{
		type = DataBuffersIDType::STAGING;
	}

	DataBuffersGenericID::DataBuffersIndexID::DataBuffersIndexID(const IDObject<AutoCleanupIndexBuffer>& ID) noexcept : ID(ID)
	{
		type = DataBuffersIDType::INDEX;
	}

	DataBuffersGenericID::DataBuffersUniformID::DataBuffersUniformID(const IDObject<AutoCleanupUniformBuffer>& ID) noexcept : ID(ID)
	{
		type = DataBuffersIDType::UNIFORM;
	}

}