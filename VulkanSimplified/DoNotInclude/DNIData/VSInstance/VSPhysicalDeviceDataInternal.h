#pragma once

#include "../../../Include/VSInstance/VSDeviceVulkan10Properties.h"
#include "../../../Include/VSInstance/VSDeviceQueueFamilyData.h"
#include "../../../Include/VSInstance/VSDevicesSupportedFormats.h"
#include "../../../Include/VSInstance/VSDeviceExtensionPacksList.h"
#include "../../../Include/VSInstance/VSDeviceVulkan10FeatureFlagsDef.h"
#include "../../../Include/VSInstance/VSDeviceSwapchainSupportData.h"
#include "../../../Include/VSCommon/VSMemoryData.h"

#include <optional>
#include <vector>
#include <vulkan/vulkan_core.h>

typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkSurfaceKHR_T* VkSurfaceKHR;

struct VkPhysicalDeviceFeatures;
struct VkPhysicalDeviceLimits;

namespace VulkanSimplified
{
	class PhysicalDeviceDataInternal
	{
	public:
		PhysicalDeviceDataInternal(VkPhysicalDevice device, VkSurfaceKHR testSurface);
		~PhysicalDeviceDataInternal();

		PhysicalDeviceDataInternal(const PhysicalDeviceDataInternal& rhs) noexcept = default;

		const DeviceVulkan10Properties& GetVulkan10Properties() const;
		const DeviceVulkan10FeatureFlags& GetVulkan10Features() const;
		const DeviceExtensionPacksList& GetDeviceExtensionPacks() const;
		const std::vector<QueueFamilyData>& GetVulkanQueueFamiliesData() const;
		const FormatsSupportedFeatures& GetFormatsSupportedFeatures() const;
		const MemoryDataList& GetAvailableMemoryDataList() const;
		const std::optional<SurfaceSupportData>& GetSurfaceSupport() const;

		VkPhysicalDevice GetPhysicalDevice() const;

		static std::vector<const char*> CompileDevicesRequestedExtensionList(const DeviceExtensionPacksList& extensionPacksList);
		static VkPhysicalDeviceFeatures CompileDevicesRequestedVulkan10Features(const DeviceVulkan10FeatureFlags& requestedFeatures);

	private:
		VkPhysicalDevice _device;

		DeviceVulkan10Properties _properties10;
		DeviceVulkan10FeatureFlags _features10;
		DeviceExtensionPacksList _extensionPacks;
		std::vector<QueueFamilyData> _queueFamilies;
		FormatsSupportedFeatures _formatsSupport;
		MemoryDataList _memoryData;
		std::optional<SurfaceSupportData> _surfaceSupport;

		DeviceVulkan10Properties CompileVulkan10Properties() const;
		DeviceVulkan10Limits CompileVulkan10DeviceLimits(const VkPhysicalDeviceLimits& deviceLimits) const;
		DeviceVulkan10FeatureFlags CompileVulkan10DeviceFeatures() const;
		DeviceExtensionPacksList CompileExtensionPacks() const;
		std::vector<QueueFamilyData> CompileQueueData(VkSurfaceKHR testSurface) const;

		DeviceType GetDeviceType(const VkPhysicalDeviceType& deviceType) const;

		FormatsSupportedFeatures CompileFormatsSupportedFeatures() const;

		void GetFirstSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatFirstFlagSetBits flagSetBit) const;
		void GetSecondSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatSecondFlagSetBits flagSetBit) const;
		void GetThirdSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatThirdFlagSetBits flagSetBit) const;
		void GetFourthSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatFourthFlagSetBits flagSetBit) const;
		void GetFifthSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatFifthFlagSetBits flagSetBit) const;
		void GetSixthSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatSixthFlagSetBits flagSetBit) const;
		void GetSeventhSetsFormatsSupportedFeatures(FormatsSupportedFeatures& optimalImageFeatureList, DataFormatSeventhFlagSetBits flagSetBit) const;

		MemoryDataList CompileAvailableMemory() const;
		MemoryTypeProperties GetMemoryTypeProperties(VkMemoryPropertyFlags propertyFlags) const;
		MemoryHeapProperties GetMemoryHeapProperties(VkMemoryHeapFlags propertyFlags) const;

		std::optional<SurfaceSupportData> CompileSurfaceSupport(VkSurfaceKHR testSurface) const;

		static void AddToConstCharVector(std::vector<const char*>& vector, const char* addedObject);
	};
}