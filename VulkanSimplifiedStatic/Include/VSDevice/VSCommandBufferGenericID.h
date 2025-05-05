#pragma once

#include <CustomLists/IDObject.h>

#include "VSCommandPoolQFGroupListDef.h"
#include "VSNIRCommandPoolDef.h"
#include "VSIRCommandPoolDef.h"

namespace VulkanSimplified
{
	enum class CommandBufferIDType : uint64_t
	{
		UNKNOWN = 0,
		NIR_PRIMARY = 0x1,
		NIR_SECONDARY = 0x2,
		IR_PRIMARY = 0x4,
		IR_SECONDARY = 0x8,
	};

	union CommandBufferGenericID
	{
		CommandBufferIDType type;

		struct
		{
			CommandBufferIDType type;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::NIRCommandPoolInternal>> commandPoolID;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::PrimaryNIRCommandBufferInternal>> commandBufferID;
		} NIRPrimaryID;

		struct
		{
			CommandBufferIDType type;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::NIRCommandPoolInternal>> commandPoolID;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::SecondaryNIRCommandBufferInternal>> commandBufferID;
		} NIRSecondaryID;

		struct
		{
			CommandBufferIDType type;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::IRCommandPoolInternal>> commandPoolID;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::PrimaryIRCommandBufferInternal>> commandBufferID;
		} IRPrimaryID;

		struct
		{
			CommandBufferIDType type;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::IRCommandPoolInternal>> commandPoolID;
			IDObject<std::unique_ptr<VulkanSimplifiedInternal::SecondaryIRCommandBufferInternal>> commandBufferID;
		} IRSecondaryID;

		CommandBufferGenericID();
		~CommandBufferGenericID();
	};
}