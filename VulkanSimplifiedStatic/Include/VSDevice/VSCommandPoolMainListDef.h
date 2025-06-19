#pragma once

#include <CustomLists/IDObjectDef.h>

#include <memory>

namespace VulkanSimplifiedInternal
{
	class CommandPoolQFGroupListInternal;
}

namespace VulkanSimplified
{
	typedef std::unique_ptr<VulkanSimplifiedInternal::CommandPoolQFGroupListInternal> CommandPoolQFGroupPointer;
}