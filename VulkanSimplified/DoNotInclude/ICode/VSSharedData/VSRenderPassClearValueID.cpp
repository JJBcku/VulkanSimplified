#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSRenderPassClearValueID.h"

namespace VulkanSimplified
{
	RenderPassClearValueID::RenderPassClearValueID() noexcept
	{
		type = static_cast<RenderPassClearValueIDType>(std::numeric_limits<uint64_t>::max());
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassDoubleColorClearValues> ID) noexcept
	{
		doubleColorID.type = RenderPassClearValueIDType::COLOR_DOUBLE;
		doubleColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassInt64ColorClearValues> ID) noexcept
	{
		int64ColorID.type = RenderPassClearValueIDType::COLOR_INT64;
		int64ColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassUInt64ColorClearValues> ID) noexcept
	{
		uint64ColorID.type = RenderPassClearValueIDType::COLOR_UINT64;
		uint64ColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassFloatColorClearValues> ID) noexcept
	{
		floatColorID.type = RenderPassClearValueIDType::COLOR_FLOAT;
		floatColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassIntColorClearValues> ID) noexcept
	{
		intColorID.type = RenderPassClearValueIDType::COLOR_INT;
		intColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassUIntColorClearValues> ID) noexcept
	{
		uintColorID.type = RenderPassClearValueIDType::COLOR_UINT;
		uintColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassDepthStencilClearValues> ID) noexcept
	{
		depthStencilID.type = RenderPassClearValueIDType::DEPTH_STENCIL;
		depthStencilID.ID = ID;
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

}