#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	struct RenderPassDoubleColorClearValues;
	struct RenderPassInt64ColorClearValues;
	struct RenderPassUInt64ColorClearValues;
	struct RenderPassFloatColorClearValues;
	struct RenderPassIntColorClearValues;
	struct RenderPassUIntColorClearValues;
	struct RenderPassDepthStencilClearValues;
}

namespace VulkanSimplified
{
	enum class RenderPassClearValueIDType : uint64_t
	{
		COLOR_DOUBLE = 0x1,
		COLOR_INT64 = 0x2,
		COLOR_UINT64 = 0x4,
		COLOR_FLOAT = 0x8,
		COLOR_INT = 0x10,
		COLOR_UINT = 0x20,
		DEPTH_STENCIL = 0x40,
	};

	union RenderPassClearValueID
	{
		RenderPassClearValueIDType type;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassDoubleColorClearValues> ID;
		} doubleColorID;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassInt64ColorClearValues> ID;
		} int64ColorID;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassUInt64ColorClearValues> ID;
		} uint64ColorID;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassFloatColorClearValues> ID;
		} floatColorID;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassIntColorClearValues> ID;
		} intColorID;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassUIntColorClearValues> ID;
		} uintColorID;

		struct
		{
			RenderPassClearValueIDType type;
			IDObject<VulkanSimplifiedInternal::RenderPassDepthStencilClearValues> ID;
		} depthStencilID;

		RenderPassClearValueID();
		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassDoubleColorClearValues> ID);
		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassInt64ColorClearValues> ID);
		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassUInt64ColorClearValues> ID);

		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassFloatColorClearValues> ID);
		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassIntColorClearValues> ID);
		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassUIntColorClearValues> ID);

		RenderPassClearValueID(IDObject<VulkanSimplifiedInternal::RenderPassDepthStencilClearValues> ID);
	};
}