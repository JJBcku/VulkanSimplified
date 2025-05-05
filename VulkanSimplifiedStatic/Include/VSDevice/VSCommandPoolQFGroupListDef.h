#pragma once

#include <CustomLists/IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class NIRCommandPoolInternal;
	class IRCommandPoolInternal;
}

namespace VulkanSimplified
{
	typedef std::unique_ptr<VulkanSimplifiedInternal::NIRCommandPoolInternal> NIRPoolPointer;
	typedef std::unique_ptr<VulkanSimplifiedInternal::IRCommandPoolInternal> IRPoolPointer;
}