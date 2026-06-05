#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSRenderPassClearValueID.h"

namespace VulkanSimplified
{
	RenderPassClearValueID::RenderPassClearValueID() noexcept
	{
		type = static_cast<RenderPassClearValueIDType>(std::numeric_limits<uint64_t>::max());
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassDoubleColorClearValues>& ID) noexcept : doubleColorID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassInt64ColorClearValues>& ID) noexcept : int64ColorID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassUInt64ColorClearValues>& ID) noexcept : uint64ColorID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassFloatColorClearValues>& ID) noexcept : floatColorID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassIntColorClearValues>& ID) noexcept : int32ColorID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassUIntColorClearValues>& ID) noexcept : uint32ColorID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const IDObject<RenderPassDepthStencilClearValues>& ID) noexcept : depthStencilID(ID)
	{
	}

	RenderPassClearValueID::RenderPassClearValueID(const RenderPassClearValueID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(rhs));
	}

	RenderPassClearValueID::~RenderPassClearValueID()
	{
	}

	RenderPassClearValueID& RenderPassClearValueID::operator=(const RenderPassClearValueID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(rhs));

		return *this;
	}

	RenderPassClearValueID::DoubleColorID::DoubleColorID(const IDObject<RenderPassDoubleColorClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::COLOR_DOUBLE;
	}

	RenderPassClearValueID::Int64ColorID::Int64ColorID(const IDObject<RenderPassInt64ColorClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::COLOR_INT64;
	}

	RenderPassClearValueID::Uint64ColorID::Uint64ColorID(const IDObject<RenderPassUInt64ColorClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::COLOR_UINT64;
	}

	RenderPassClearValueID::FloatColorID::FloatColorID(const IDObject<RenderPassFloatColorClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::COLOR_FLOAT;
	}

	RenderPassClearValueID::Int32ColorID::Int32ColorID(const IDObject<RenderPassIntColorClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::COLOR_INT32;
	}

	RenderPassClearValueID::Uint32ColorID::Uint32ColorID(const IDObject<RenderPassUIntColorClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::COLOR_UINT32;
	}

	RenderPassClearValueID::DepthStencilID::DepthStencilID(const IDObject<RenderPassDepthStencilClearValues>& ID) noexcept : ID(ID)
	{
		type = RenderPassClearValueIDType::DEPTH_STENCIL;
	}

}