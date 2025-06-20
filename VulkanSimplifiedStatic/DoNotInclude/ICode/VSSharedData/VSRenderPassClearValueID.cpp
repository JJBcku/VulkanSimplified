#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSRenderPassClearValueID.h"

namespace VulkanSimplified
{
	RenderPassClearValueID::RenderPassClearValueID()
	{
		type = static_cast<RenderPassClearValueIDType>(std::numeric_limits<uint64_t>::max());
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassDoubleColorClearValues> ID)
	{
		doubleColorID.type = RenderPassClearValueIDType::COLOR_DOUBLE;
		doubleColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassInt64ColorClearValues> ID)
	{
		int64ColorID.type = RenderPassClearValueIDType::COLOR_INT64;
		int64ColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassUInt64ColorClearValues> ID)
	{
		uint64ColorID.type = RenderPassClearValueIDType::COLOR_UINT64;
		uint64ColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassFloatColorClearValues> ID)
	{
		floatColorID.type = RenderPassClearValueIDType::COLOR_FLOAT;
		floatColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassIntColorClearValues> ID)
	{
		intColorID.type = RenderPassClearValueIDType::COLOR_INT;
		intColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassUIntColorClearValues> ID)
	{
		uintColorID.type = RenderPassClearValueIDType::COLOR_UINT;
		uintColorID.ID = ID;
	}

	RenderPassClearValueID::RenderPassClearValueID(IDObject<RenderPassDepthStencilClearValues> ID)
	{
		depthStencilID.type = RenderPassClearValueIDType::DEPTH_STENCIL;
		depthStencilID.ID = ID;
	}
}