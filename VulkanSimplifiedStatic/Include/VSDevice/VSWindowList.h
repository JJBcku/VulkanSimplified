#pragma once

template<class T>
class IDObject;

namespace VulkanSimplifiedInternal
{
	class WindowListInternal;
	class WindowInternal;
}

namespace VulkanSimplified
{
	struct WindowCreationData;

	class WindowList
	{
	public:
		WindowList(VulkanSimplifiedInternal::WindowListInternal& ref);
		~WindowList();

		IDObject<VulkanSimplifiedInternal::WindowInternal> CreateWindow(const WindowCreationData& creationData, size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::WindowListInternal& _internal;
	};
}
