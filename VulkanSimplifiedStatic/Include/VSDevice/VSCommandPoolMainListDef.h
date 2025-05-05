#pragma once

#include <CustomLists/IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class CommandPoolQFGroupListInternal;
}

namespace VulkanSimplified
{
	typedef std::unique_ptr<VulkanSimplifiedInternal::CommandPoolQFGroupListInternal> CommandPoolQFGroupPointer;
}