#pragma once

#include <memory>

namespace VulkanSimplifiedInternal
{
	class WindowInternal;
}

namespace VulkanSimplified
{
	typedef std::unique_ptr<VulkanSimplifiedInternal::WindowInternal> WindowPointer;
}