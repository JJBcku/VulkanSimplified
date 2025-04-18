#pragma once

#include "../../Include/VSInstance/VSDeviceVulkan10Properties.h"
#include "../../Include/VSInstance/VSDeviceQueueFamilyData.h"
#include "../../Include/VSInstance/VSDevicesSupportedFormats.h"
#include "../../Include/VSInstance/VSDeviceExtensionPacksList.h"
#include "../../Include/VSInstance/VSDeviceVulkan10Features.h"
#include "../../Include/VSInstance/VSDeviceSwapchainSupportData.h"
#include "../../Include/VSCommon/VSMemoryData.h"

namespace VulkanSimplifiedInternal
{
	class PhysicalDeviceDataInternal
	{
	public:
		PhysicalDeviceDataInternal(VkPhysicalDevice device, VkSurfaceKHR testSurface);
		~PhysicalDeviceDataInternal();

		PhysicalDeviceDataInternal(const PhysicalDeviceDataInternal& rhs) noexcept = default;

		const VulkanSimplified::DeviceVulkan10Properties& GetVulkan10Properties() const;
		const VulkanSimplified::DeviceVulkan10FeatureFlags& GetVulkan10Features() const;
		const VulkanSimplified::DeviceExtensionPacksList& GetDeviceExtensionPacks() const;
		const std::vector<VulkanSimplified::QueueFamilyData>& GetVulkanQueueFamiliesData() const;
		const VulkanSimplified::FormatsSupportedFeatures& GetFormatsSupportedFeatures() const;
		const VulkanSimplified::MemoryDataList& GetAvailableMemoryDataList() const;
		const std::optional<VulkanSimplified::SurfaceSupportData>& GetSurfaceSupport() const;

		VkPhysicalDevice GetPhysicalDevice() const;

		static std::vector<const char*> CompileDevicesRequestedExtensionList(const VulkanSimplified::DeviceExtensionPacksList& extensionPacksList);
		static VkPhysicalDeviceFeatures CompileDevicesRequestedVulkan10Features(const VulkanSimplified::DeviceVulkan10FeatureFlags& requestedFeatures);

	private:
		VkPhysicalDevice _device;

		VulkanSimplified::DeviceVulkan10Properties _properties10;
		VulkanSimplified::DeviceVulkan10FeatureFlags _features10;
		VulkanSimplified::DeviceExtensionPacksList _extensionPacks;
		std::vector<VulkanSimplified::QueueFamilyData> _queueFamilies;
		VulkanSimplified::FormatsSupportedFeatures _formatsSupport;
		VulkanSimplified::MemoryDataList _memoryData;
		std::optional<VulkanSimplified::SurfaceSupportData> _surfaceSupport;

		VulkanSimplified::DeviceVulkan10Properties CompileVulkan10Properties() const;
		VulkanSimplified::DeviceVulkan10Limits CompileVulkan10DeviceLimits(const VkPhysicalDeviceLimits& deviceLimits) const;
		VulkanSimplified::DeviceVulkan10FeatureFlags CompileVulkan10DeviceFeatures() const;
		VulkanSimplified::DeviceExtensionPacksList CompileExtensionPacks() const;
		std::vector<VulkanSimplified::QueueFamilyData> CompileQueueData(VkSurfaceKHR testSurface) const;

		VulkanSimplified::DeviceType GetDeviceType(const VkPhysicalDeviceType& deviceType) const;

		VulkanSimplified::FormatsSupportedFeatures CompileFormatsSupportedFeatures() const;

		void GetFirstSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatFirstFlagSetBits flagSetBit) const;
		void GetSecondSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatSecondFlagSetBits flagSetBit) const;
		void GetThirdSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatThirdFlagSetBits flagSetBit) const;
		void GetFourthSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatFourthFlagSetBits flagSetBit) const;
		void GetFifthSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatFifthFlagSetBits flagSetBit) const;
		void GetSixthSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatSixthFlagSetBits flagSetBit) const;
		void GetSeventhSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& optimalImageFeatureList, VulkanSimplified::DataFormatSeventhFlagSetBits flagSetBit) const;

		VulkanSimplified::MemoryDataList CompileAvailableMemory() const;
		VulkanSimplified::MemoryTypeProperties GetMemoryTypeProperties(VkMemoryPropertyFlags propertyFlags) const;
		VulkanSimplified::MemoryHeapProperties GetMemoryHeapProperties(VkMemoryHeapFlags propertyFlags) const;

		std::optional<VulkanSimplified::SurfaceSupportData> CompileSurfaceSupport(VkSurfaceKHR testSurface) const;

		static void AddToConstCharVector(std::vector<const char*>& vector, const char* addedObject);
	};
}