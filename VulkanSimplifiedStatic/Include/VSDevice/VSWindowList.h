#pragma once

namespace VulkanSimplifiedInternal
{
	class WindowListInternal;
}

namespace VulkanSimplified
{
	class WindowList
	{
	public:
		WindowList(VulkanSimplifiedInternal::WindowListInternal& ref);
		~WindowList();

	private:
		VulkanSimplifiedInternal::WindowListInternal& _internal;
	};
}
