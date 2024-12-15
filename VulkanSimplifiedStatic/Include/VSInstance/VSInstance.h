#pragma once

namespace VulkanSimplifiedInternal
{
	class InstanceInternal;
}

namespace VulkanSimplified
{
	class Instance
	{
	public:
		Instance(VulkanSimplifiedInternal::InstanceInternal& ref);
		~Instance();

		Instance& operator=(const Instance&) noexcept = delete;

	private:
		VulkanSimplifiedInternal::InstanceInternal& _internal;
	};
}