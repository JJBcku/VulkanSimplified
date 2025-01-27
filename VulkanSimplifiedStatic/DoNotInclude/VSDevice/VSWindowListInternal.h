#pragma once

namespace VulkanSimplified
{
	struct WindowListInitialCapacities;
}

namespace VulkanSimplifiedInternal
{
	class WindowListInternal
	{
	public:
		WindowListInternal(const VulkanSimplified::WindowListInitialCapacities& initalCapacities);
		~WindowListInternal();

	private:
			size_t stump;
	};
}