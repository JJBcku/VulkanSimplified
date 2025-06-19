#pragma once

#include <CustomLists/IDObjectDef.h>

#include <memory>

namespace VulkanSimplifiedInternal
{
	class PrimaryIRCommandBufferInternal;
	class SecondaryIRCommandBufferInternal;
}

namespace VulkanSimplified
{
	typedef std::unique_ptr<VulkanSimplifiedInternal::PrimaryIRCommandBufferInternal> PrimaryIRPointer;
	typedef std::unique_ptr<VulkanSimplifiedInternal::SecondaryIRCommandBufferInternal> SecondaryIRPointer;
}