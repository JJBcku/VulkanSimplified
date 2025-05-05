#pragma once

#include <CustomLists/IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class PrimaryNIRCommandBufferInternal;
	class SecondaryNIRCommandBufferInternal;
}

namespace VulkanSimplified
{
	typedef std::unique_ptr<VulkanSimplifiedInternal::PrimaryNIRCommandBufferInternal> PrimaryNIRPointer;
	typedef std::unique_ptr<VulkanSimplifiedInternal::SecondaryNIRCommandBufferInternal> SecondaryNIRPointer;
}