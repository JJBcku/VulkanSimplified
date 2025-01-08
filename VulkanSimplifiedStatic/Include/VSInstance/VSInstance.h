#pragma once

namespace VulkanSimplifiedInternal
{
	class InstanceInternal;
}

namespace VulkanSimplified
{
	class PhysicalDeviceData;

	class Instance
	{
	public:
		Instance(VulkanSimplifiedInternal::InstanceInternal& ref);
		~Instance();

		Instance& operator=(const Instance&) noexcept = delete;

		size_t GetAvailableDevicesCount() const;

		PhysicalDeviceData GetPhysicalDeviceData(size_t deviceIndex);

		const PhysicalDeviceData GetPhysicalDeviceData(size_t deviceIndex) const;

	private:
		VulkanSimplifiedInternal::InstanceInternal& _internal;
	};
}