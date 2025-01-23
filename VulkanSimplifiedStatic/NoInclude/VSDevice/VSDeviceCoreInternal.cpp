#include "VSDeviceNIpch.h"
#include "VSDeviceCoreInternal.h"

#include "../VSInstance/VsLogicalDeviceInternalCreationData.h"

namespace VulkanSimplifiedInternal
{
	DeviceCoreInternal::DeviceCoreInternal(VkInstance instance, const LogicalDeviceInternalCreationData& creationData, const PhysicalDeviceDataInternal& physicalDeviceData) :
		_physicalDeviceData(physicalDeviceData)
	{
		_instance = instance;
		_device = VK_NULL_HANDLE;

		_apiVersion = creationData.apiVersion;
		_padding = creationData.padding;

		_vulkan10EnabledFeatures = creationData.vulkan10EnabledFeatures;
		_requestedExtensionPacks = creationData.requestedExtensionPacks;

		{
			VkDeviceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

			createInfo.queueCreateInfoCount = static_cast<std::uint32_t>(creationData.queueInfos.size());
			createInfo.pQueueCreateInfos = creationData.queueInfos.data();

			createInfo.enabledExtensionCount = static_cast<std::uint32_t>(creationData.enabledExtensionsList.size());
			createInfo.ppEnabledExtensionNames = creationData.enabledExtensionsList.data();

			createInfo.pEnabledFeatures = &creationData.features;

			if (vkCreateDevice(_physicalDeviceData.GetPhysicalDevice(), &createInfo, nullptr, &_device) != VK_SUCCESS)
				throw std::runtime_error("DeviceCoreInternal::DeviceCoreInternal Error: Program failed to create the device!");
		}

		{
			size_t totalQueueCount = 0;

			for (size_t i = 0; i < creationData.queueInfos.size(); ++i)
			{
				if (totalQueueCount + creationData.queueInfos[i].queueCount < totalQueueCount)
					throw std::runtime_error("DeviceCoreInternal::DeviceCoreInternal Error: Total queues count overflowed!");

				totalQueueCount += creationData.queueInfos[i].queueCount;
			}

			_queues.resize(totalQueueCount, { VK_NULL_HANDLE, 0 });

			size_t currentQueueIndex = 0;

			for (size_t i = 0; i < creationData.queueInfos.size(); ++i)
			{
				for (std::uint32_t j = 0; j < creationData.queueInfos[i].queueCount; ++j)
				{
					auto& queueFamilyData = creationData.queueInfos[i];
					auto& queueData = _queues[currentQueueIndex];

					queueData.second = queueFamilyData.queueFamilyIndex;

					vkGetDeviceQueue(_device, queueFamilyData.queueFamilyIndex, j, &queueData.first);

					if (queueData.first == VK_NULL_HANDLE)
						throw std::runtime_error("DeviceCoreInternal::DeviceCoreInternal Error: Program failed to get a device queue!");

					currentQueueIndex++;
				}
			}

		}
	}

	DeviceCoreInternal::~DeviceCoreInternal()
	{
		if (_device != VK_NULL_HANDLE)
		{
			vkDestroyDevice(_device, nullptr);
		}
	}

	VkDevice DeviceCoreInternal::GetDevice() const
	{
		return _device;
	}

	uint32_t DeviceCoreInternal::GetDevicesApiVersion() const
	{
		return _apiVersion;
	}

	VkQueue DeviceCoreInternal::GetQueue(size_t queueIndex) const
	{
		if (queueIndex >= _queues.size())
			throw std::runtime_error("DeviceCoreInternal::GetQueue Error: Program tried to read past the end of queue data vector!");

		return _queues[queueIndex].first;
	}

	uint32_t DeviceCoreInternal::GetQueuesFamily(size_t queueIndex) const
	{
		if (queueIndex >= _queues.size())
			throw std::runtime_error("DeviceCoreInternal::GetQueuesFamily Error: Program tried to read past the end of queue data vector!");

		return _queues[queueIndex].second;
	}

	VulkanSimplified::DeviceVulkan10FeatureFlags DeviceCoreInternal::GetVulkan10EnabledFeatures() const
	{
		return _vulkan10EnabledFeatures;
	}

	const VulkanSimplified::DeviceExtensionPacksList& DeviceCoreInternal::GetDevicesEnabledExtensionPacks() const
	{
		return _requestedExtensionPacks;
	}

	PhysicalDeviceDataInternal& DeviceCoreInternal::GetDevicesPhysicalData()
	{
		return _physicalDeviceData;
	}

	const PhysicalDeviceDataInternal& DeviceCoreInternal::GetDevicesPhysicalData() const
	{
		return _physicalDeviceData;
	}

}