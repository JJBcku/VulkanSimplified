#pragma once

namespace VulkanSimplifiedInternal
{
	class InstanceInternal;
}

namespace VulkanSimplified
{
	class PhysicalDeviceData;
	class DeviceMain;

	struct LogicalDeviceCreationData;

	class Instance
	{
	public:
		Instance(VulkanSimplifiedInternal::InstanceInternal& ref);
		~Instance();

		Instance& operator=(const Instance&) noexcept = delete;

		size_t GetAvailableDevicesCount() const;

		PhysicalDeviceData GetPhysicalDeviceData(size_t deviceIndex);
		DeviceMain GetChoosenDevicesMainClass();

		const PhysicalDeviceData GetPhysicalDeviceData(size_t deviceIndex) const;
		const DeviceMain GetChoosenDevicesMainClass() const;

		void CreateLogicalDevice(const LogicalDeviceCreationData& creationData);

	private:
		VulkanSimplifiedInternal::InstanceInternal& _internal;
	};
}