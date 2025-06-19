#include "VSInstanceNIpch.h"
#include "VSPhysicalDeviceDataInternal.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"
#include "../VSCommon/VSCStringsComparison.h"

#include "../../Include/VSCommon/VSImageUsageFlags.h"
#include "../../Include/VSCommon/VSSurfacePresentModes.h"

#include "../../Include/VSInstance/VSDeviceVulkan10FeatureFlags.h"

namespace VulkanSimplifiedInternal
{

	PhysicalDeviceDataInternal::PhysicalDeviceDataInternal(VkPhysicalDevice device, VkSurfaceKHR testSurface) : _device(device)
	{
		_properties10 = CompileVulkan10Properties();
		_features10 = CompileVulkan10DeviceFeatures();
		_extensionPacks = CompileExtensionPacks();

		if (!_extensionPacks.swapchainBase)
			testSurface = VK_NULL_HANDLE;

		_queueFamilies = CompileQueueData(testSurface);
		_formatsSupport = CompileFormatsSupportedFeatures();
		_memoryData = CompileAvailableMemory();
		_surfaceSupport = CompileSurfaceSupport(testSurface);
	}

	PhysicalDeviceDataInternal::~PhysicalDeviceDataInternal()
	{
	}

	const VulkanSimplified::DeviceVulkan10Properties& PhysicalDeviceDataInternal::GetVulkan10Properties() const
	{
		return _properties10;
	}

	const VulkanSimplified::DeviceVulkan10FeatureFlags& PhysicalDeviceDataInternal::GetVulkan10Features() const
	{
		return _features10;
	}

	const VulkanSimplified::DeviceExtensionPacksList& PhysicalDeviceDataInternal::GetDeviceExtensionPacks() const
	{
		return _extensionPacks;
	}

	const std::vector<VulkanSimplified::QueueFamilyData>& PhysicalDeviceDataInternal::GetVulkanQueueFamiliesData() const
	{
		return _queueFamilies;
	}

	const VulkanSimplified::FormatsSupportedFeatures& PhysicalDeviceDataInternal::GetFormatsSupportedFeatures() const
	{
		return _formatsSupport;
	}

	const VulkanSimplified::MemoryDataList& PhysicalDeviceDataInternal::GetAvailableMemoryDataList() const
	{
		return _memoryData;
	}

	const std::optional<VulkanSimplified::SurfaceSupportData>& PhysicalDeviceDataInternal::GetSurfaceSupport() const
	{
		return _surfaceSupport;
	}

	VkPhysicalDevice PhysicalDeviceDataInternal::GetPhysicalDevice() const
	{
		return _device;
	}

	std::vector<const char*> PhysicalDeviceDataInternal::CompileDevicesRequestedExtensionList(const VulkanSimplified::DeviceExtensionPacksList& extensionPacksList)
	{
		std::vector<const char*> ret;
		ret.reserve(16);

		if (extensionPacksList.swapchainBase)
		{
			ret.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		if (!ret.empty())
		{
			std::stable_sort(ret.begin(), ret.end(), &ISFirstCStringLesser);
			ret.erase(std::unique(ret.begin(), ret.end(), &AreCStringEqual), ret.end());
		}

		return ret;
	}

	VkPhysicalDeviceFeatures PhysicalDeviceDataInternal::CompileDevicesRequestedVulkan10Features(const VulkanSimplified::DeviceVulkan10FeatureFlags& requestedFeatures)
	{
		VkPhysicalDeviceFeatures ret{};

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_FULL_DRAW_INDEX_UINT32) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_FULL_DRAW_INDEX_UINT32)
			ret.fullDrawIndexUint32 = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_INDEPENDENT_BLEND) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_INDEPENDENT_BLEND)
			ret.independentBlend = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_FILL_MODE_NONSOLID) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_FILL_MODE_NONSOLID)
			ret.fillModeNonSolid = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY)
			ret.samplerAnisotropy = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ETC2) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ETC2)
			ret.textureCompressionETC2 = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR)
			ret.textureCompressionASTC_LDR = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_BC) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_BC)
			ret.textureCompressionBC = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_FLOAT64) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_FLOAT64)
			ret.shaderFloat64 = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_INT64) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_INT64)
			ret.shaderInt64 = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_INT16) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_INT16)
			ret.shaderInt16 = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_RESIDENCY) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_RESIDENCY)
			ret.shaderResourceResidency = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_MINIMUM_LOD) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_MINIMUM_LOD)
			ret.shaderResourceMinLod = VK_TRUE;

		if ((requestedFeatures & VulkanSimplified::DEVICE_VULKAN10_FEATURE_SAMPLE_RATE_SHADING) == VulkanSimplified::DEVICE_VULKAN10_FEATURE_SAMPLE_RATE_SHADING)
			ret.sampleRateShading = VK_TRUE;

		return ret;
	}

	VulkanSimplified::DeviceVulkan10Properties PhysicalDeviceDataInternal::CompileVulkan10Properties() const
	{
		VulkanSimplified::DeviceVulkan10Properties ret;

		VkPhysicalDeviceProperties vulkanProperties{};

		vkGetPhysicalDeviceProperties(_device, &vulkanProperties);

		ret.apiMaxSupportedVersion = vulkanProperties.apiVersion;
		ret.driverVersion = vulkanProperties.driverVersion;
		ret.vendorID = vulkanProperties.vendorID;
		ret.deviceID = vulkanProperties.deviceID;
		ret.deviceType = GetDeviceType(vulkanProperties.deviceType);
		ret.deviceName = std::string(vulkanProperties.deviceName);

		std::memcpy(ret.pipelineCacheUUID.data(), vulkanProperties.pipelineCacheUUID, sizeof(vulkanProperties.pipelineCacheUUID));

		ret.limits = CompileVulkan10DeviceLimits(vulkanProperties.limits);

		return ret;
	}

	VulkanSimplified::DeviceVulkan10Limits PhysicalDeviceDataInternal::CompileVulkan10DeviceLimits(const VkPhysicalDeviceLimits& deviceLimits) const
	{
		VulkanSimplified::DeviceVulkan10Limits ret;

		ret.maxImageSizes.maxImageDimension1D = deviceLimits.maxImageDimension1D;
		ret.maxImageSizes.maxImageDimension2D = deviceLimits.maxImageDimension2D;
		ret.maxImageSizes.maxImageDimension3D = deviceLimits.maxImageDimension3D;
		ret.maxImageSizes.maxImageArrayLayers = deviceLimits.maxImageArrayLayers;

		ret.maxUniformBufferRange = deviceLimits.maxUniformBufferRange;
		ret.maxStorageBufferRange = deviceLimits.maxStorageBufferRange;
		ret.maxPushConstantsSize = deviceLimits.maxPushConstantsSize;

		ret.maxMemoryAllocationCount = deviceLimits.maxMemoryAllocationCount;
		ret.maxSamplerAllocationCount = deviceLimits.maxSamplerAllocationCount;

		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxBoundDescriptorSets = deviceLimits.maxBoundDescriptorSets;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorSamplers = deviceLimits.maxPerStageDescriptorSamplers;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorUniformBuffers = deviceLimits.maxPerStageDescriptorUniformBuffers;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorStorageBuffers = deviceLimits.maxPerStageDescriptorStorageBuffers;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorSampledImages = deviceLimits.maxPerStageDescriptorSampledImages;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorStorageImages = deviceLimits.maxPerStageDescriptorStorageImages;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageDescriptorInputAttachments = deviceLimits.maxPerStageDescriptorInputAttachments;
		ret.descriptorSetLimits.descriptorSetBindingsLimit.maxPerStageResources = deviceLimits.maxPerStageResources;

		ret.descriptorSetLimits.maxDescriptorSetSamplers = deviceLimits.maxDescriptorSetSamplers;
		ret.descriptorSetLimits.maxDescriptorSetUniformBuffers = deviceLimits.maxDescriptorSetUniformBuffers;
		ret.descriptorSetLimits.maxDescriptorSetUniformBuffersDynamic = deviceLimits.maxDescriptorSetUniformBuffersDynamic;
		ret.descriptorSetLimits.maxDescriptorSetStorageBuffers = deviceLimits.maxDescriptorSetStorageBuffers;
		ret.descriptorSetLimits.maxDescriptorSetStorageBuffersDynamic = deviceLimits.maxDescriptorSetStorageBuffersDynamic;
		ret.descriptorSetLimits.maxDescriptorSetSampledImages = deviceLimits.maxDescriptorSetSampledImages;
		ret.descriptorSetLimits.maxDescriptorSetStorageImages = deviceLimits.maxDescriptorSetStorageImages;
		ret.descriptorSetLimits.maxDescriptorSetInputAttachments = deviceLimits.maxDescriptorSetInputAttachments;

		ret.vertexShaderLimit.maxVertexInputAttributes = deviceLimits.maxVertexInputAttributes;
		ret.vertexShaderLimit.maxVertexInputBindings = deviceLimits.maxVertexInputBindings;
		ret.vertexShaderLimit.maxVertexInputAttributeOffset = deviceLimits.maxVertexInputAttributeOffset;
		ret.vertexShaderLimit.maxVertexInputBindingStride = deviceLimits.maxVertexInputBindingStride;
		ret.vertexShaderLimit.maxVertexOutputComponents = deviceLimits.maxVertexOutputComponents;

		ret.fragmentShaderLimit.maxFragmentInputComponents = deviceLimits.maxFragmentInputComponents;
		ret.fragmentShaderLimit.maxFragmentOutputAttachments = deviceLimits.maxFragmentOutputAttachments;
		ret.fragmentShaderLimit.maxFragmentDualSrcAttachments = deviceLimits.maxFragmentDualSrcAttachments;
		ret.fragmentShaderLimit.maxFragmentCombinedOutputResources = deviceLimits.maxFragmentCombinedOutputResources;

		ret.subPixelPrecisionBits = deviceLimits.subPixelPrecisionBits;
		ret.mipmapPrecisionBits = deviceLimits.mipmapPrecisionBits;

		ret.maxDrawIndexedIndexValue = deviceLimits.maxDrawIndexedIndexValue;

		ret.maxSamplerLodBias = deviceLimits.maxSamplerLodBias;
		ret.maxSamplerAnisotropy = deviceLimits.maxSamplerAnisotropy;

		ret.viewportLimits.maxViewports = deviceLimits.maxViewports;
		ret.viewportLimits.maxViewportDimensionsX = deviceLimits.maxViewportDimensions[0];
		ret.viewportLimits.maxViewportDimensionsY = deviceLimits.maxViewportDimensions[1];
		ret.viewportLimits.viewportBoundsRangeMin = deviceLimits.viewportBoundsRange[0];
		ret.viewportLimits.viewportBoundsRangeMax = deviceLimits.viewportBoundsRange[1];
		ret.viewportLimits.viewportSubPixelBits = deviceLimits.viewportSubPixelBits;

		ret.framebufferLimits.maxFramebufferWidth = deviceLimits.maxFramebufferWidth;
		ret.framebufferLimits.maxFramebufferHeight = deviceLimits.maxFramebufferHeight;
		ret.framebufferLimits.maxFramebufferLayers = deviceLimits.maxFramebufferLayers;
		ret.framebufferLimits.framebufferColorSampleCounts = deviceLimits.framebufferColorSampleCounts;
		ret.framebufferLimits.framebufferDepthSampleCounts = deviceLimits.framebufferDepthSampleCounts;
		ret.framebufferLimits.framebufferStencilSampleCounts = deviceLimits.framebufferStencilSampleCounts;
		ret.framebufferLimits.framebufferNoAttachmentsSampleCounts = deviceLimits.framebufferNoAttachmentsSampleCounts;

		ret.maxColorAttachments = deviceLimits.maxColorAttachments;

		ret.samplingLimits.sampledImageColorSampleCounts = deviceLimits.sampledImageColorSampleCounts;
		ret.samplingLimits.sampledImageIntegerSampleCounts = deviceLimits.sampledImageIntegerSampleCounts;
		ret.samplingLimits.sampledImageDepthSampleCounts = deviceLimits.sampledImageDepthSampleCounts;
		ret.samplingLimits.sampledImageStencilSampleCounts = deviceLimits.sampledImageStencilSampleCounts;
		ret.samplingLimits.storageImageSampleCounts = deviceLimits.storageImageSampleCounts;

		return ret;
	}

	VulkanSimplified::DeviceVulkan10FeatureFlags PhysicalDeviceDataInternal::CompileVulkan10DeviceFeatures() const
	{
		VulkanSimplified::DeviceVulkan10FeatureFlags ret = 0;

		VkPhysicalDeviceFeatures deviceFeatures{};
		vkGetPhysicalDeviceFeatures(_device, &deviceFeatures);

		if (deviceFeatures.fullDrawIndexUint32 == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_FULL_DRAW_INDEX_UINT32;

		if (deviceFeatures.independentBlend == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_INDEPENDENT_BLEND;

		if (deviceFeatures.fillModeNonSolid == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_FILL_MODE_NONSOLID;

		if (deviceFeatures.samplerAnisotropy == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY;

		if (deviceFeatures.textureCompressionETC2 == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ETC2;

		if (deviceFeatures.textureCompressionASTC_LDR == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR;

		if (deviceFeatures.textureCompressionBC == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_BC;

		if (deviceFeatures.shaderFloat64 == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_FLOAT64;

		if (deviceFeatures.shaderInt64 == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_INT64;

		if (deviceFeatures.shaderInt16 == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_INT16;

		if (deviceFeatures.shaderResourceResidency == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_RESIDENCY;

		if (deviceFeatures.shaderResourceMinLod == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_MINIMUM_LOD;

		if (deviceFeatures.sampleRateShading == VK_TRUE)
			ret |= VulkanSimplified::DEVICE_VULKAN10_FEATURE_SAMPLE_RATE_SHADING;

		return ret;
	}

	VulkanSimplified::DeviceExtensionPacksList PhysicalDeviceDataInternal::CompileExtensionPacks() const
	{
		VulkanSimplified::DeviceExtensionPacksList ret;

		std::vector<VkExtensionProperties> availableExtensions;
		uint32_t size = 0;

		auto result = vkEnumerateDeviceExtensionProperties(_device, nullptr, &size, nullptr);

		if (result != VK_SUCCESS)
			throw std::runtime_error("PhysicalDeviceDataInternal::CompileExtensionPacks Error: Program failed to get extension list's size!");

		if (size > 0)
		{
			availableExtensions.resize(size);

			result = vkEnumerateDeviceExtensionProperties(_device, nullptr, &size, availableExtensions.data());

			if (result != VK_SUCCESS)
				throw std::runtime_error("PhysicalDeviceDataInternal::CompileExtensionPacks Error: Program failed enumerate extensions!");

			for (size_t i = 0; i < availableExtensions.size(); i++)
			{
				const char* extensionName = availableExtensions[i].extensionName;

				if (std::strcmp(extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
				{
					ret.swapchainBase = true;
				}
			}
		}

		return ret;
	}

	std::vector<VulkanSimplified::QueueFamilyData> PhysicalDeviceDataInternal::CompileQueueData(VkSurfaceKHR testSurface) const
	{
		std::vector<VulkanSimplified::QueueFamilyData> ret;

		uint32_t size = 0;
		std::vector<VkQueueFamilyProperties> queueFamilies;

		vkGetPhysicalDeviceQueueFamilyProperties(_device, &size, nullptr);

		if (size > 0)
		{
			queueFamilies.resize(size);
			vkGetPhysicalDeviceQueueFamilyProperties(_device, &size, queueFamilies.data());

			ret.resize(size);

			for (uint32_t i = 0; i < size; i++)
			{
				auto& family = queueFamilies[i];
				auto& queueData = ret[i];

				queueData.queueTypes = family.queueFlags;
				queueData.queueCount = family.queueCount;
				queueData.timespampValidBits = family.timestampValidBits;
				queueData.minImageTransferGranularityWidth = family.minImageTransferGranularity.width;
				queueData.minImageTransferGranularityHeight = family.minImageTransferGranularity.height;
				queueData.minImageTransferGranularityDepth = family.minImageTransferGranularity.depth;

				if (testSurface != VK_NULL_HANDLE)
				{
					VkBool32 presentationSupport = VK_FALSE;

					if (vkGetPhysicalDeviceSurfaceSupportKHR(_device, i, testSurface, &presentationSupport) != VK_SUCCESS)
						throw std::runtime_error("PhysicalDeviceDataInternal::CompileQueueData Error: Program failed to query queue families support for presenting surfaces!");

					if (presentationSupport == VK_TRUE)
						queueData.presentationSupport = VulkanSimplified::BOOL64_TRUE;
				}
			}
		}

		return ret;
	}

	VulkanSimplified::DeviceType PhysicalDeviceDataInternal::GetDeviceType(const VkPhysicalDeviceType& deviceType) const
	{
		VulkanSimplified::DeviceType ret = VulkanSimplified::DeviceType::OTHER;

		switch (deviceType)
		{
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			ret = VulkanSimplified::DeviceType::INTERGRATED_GPU;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			ret = VulkanSimplified::DeviceType::DISCRETE_GPU;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			ret = VulkanSimplified::DeviceType::VIRTUAL_GPU;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			ret = VulkanSimplified::DeviceType::CPU;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:
		default:
			break;
		}

		return ret;
	}

	VulkanSimplified::FormatsSupportedFeatures PhysicalDeviceDataInternal::CompileFormatsSupportedFeatures() const
	{
		VulkanSimplified::FormatsSupportedFeatures ret;

		{
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A1_RGB5_UNORM_PACK16);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_BGR10_SINT_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_BGR10_SNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_BGR10_SSCALED_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_BGR10_UINT_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_BGR10_UNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_BGR10_USCALED_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_RGB10_SINT_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_RGB10_SNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_RGB10_SSCALED_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_RGB10_UINT_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_RGB10_UNORM_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_A2_RGB10_USCALED_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_SINT_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_SNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_SRGB_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_SSCALED_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_UINT_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_UNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ABGR8_USCALED_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X10_SRGB_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X10_UNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X5_SRGB_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X5_UNORM_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X6_SRGB_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X6_UNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X8_SRGB_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_10X8_UNORM_PACK32);

			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_12X10_SRGB_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_12X10_UNORM_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_12X10_SRGB_PACK32);
			GetFirstSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_12X10_UNORM_PACK32);
		}

		{
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_4X4_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_4X4_UNORM_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_5X4_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_5X4_UNORM_PACK32);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_5X5_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_5X5_UNORM_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_6X5_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_6X5_UNORM_PACK32);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_6X6_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_6X6_UNORM_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_8X5_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_8X5_UNORM_PACK32);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_8X6_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_8X6_UNORM_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_8X8_SRGB_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ASTC_8X8_UNORM_PACK32);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_B10_GR11_UFLOAT_PACK32);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_B10X6_G10X6_R10X6_G10X6_422_UNORM_4PACK16);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_B12X4_G12X4_R12X4_G12X4_422_UNORM_4PACK16);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRG16_422_UNORM);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA4_UNORM_PACK16);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGR5_A1_UNORM_PACK16);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_B5_G6_R5_UNORM_PACK16);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGR8_SINT);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGR8_SNORM);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGR8_SRGB);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGR8_UINT);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGR8_UNORM);

			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_SINT);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_SNORM);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_SRGB);
			GetSecondSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_SSCALED);
		}

		{
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_UINT);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_UNORM);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRA8_USCALED);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BGRG8_422_UNORM);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC1_RGB_SRGB_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC1_RGB_UNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC1_RGBA_SRGB_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC1_RGBA_UNORM_BLOCK);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC2_SRGB_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC2_UNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC3_SRGB_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC3_UNORM_BLOCK);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC4_SNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC4_UNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC5_SNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC5_UNORM_BLOCK);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC6H_SFLOAT_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC6H_UFLOAT_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC7_SRGB_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_BC7_UNORM_BLOCK);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_D16_UNORM);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_D16_UNORM_S8_UINT);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_D24_UNORM_S8_UINT);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_D32_SFLOAT);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_D32_SFLOAT_S8_UINT);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_E5_BGR9_UFLOAT_PACK32);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_EAC_R11_SNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_EAC_R11_UNORM_BLOCK);

			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_EAC_RG11_SNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_EAC_RG11_UNORM_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ETC2_RGB8_SRGB_BLOCK);
			GetThirdSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ETC2_RGB8_UNORM_BLOCK);
		}

		{
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ETC2_RGB8_A1_SRGB_BLOCK);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ETC2_RGB8_A1_UNORM_BLOCK);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ETC2_RGBA8_SRGB_BLOCK);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_ETC2_RGBA8_UNORM_BLOCK);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G10X6_BR10X6_2PLANE_420_UNORM_3PACK16);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G10X6_BR10X6_2PLANE_422_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G10X6_B10X6_G10X6_R10X6_422_UNORM_4PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G12X4_BR12X4_2PLANE_420_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G12X4_BR12X4_2PLANE_422_UNORM_3PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G12X4_B12X4_G12X4_R12X4_422_UNORM_4PACK16);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G16_B16_R16_3PLANE_420_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G16_B16_R16_3PLANE_422_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G16_BR16_2PLANE_420_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G16_BR16_2PLANE_422_UNORM);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_GBGR16_422_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G8_B8_R8_3PLANE_420_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G8_B8_R8_3PLANE_422_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G8_B8_R8_3PLANE_444_UNORM);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G8_BR8_2PLANE_420_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_G8_BR8_2PLANE_422_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_GBGR8_422_UNORM);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R10X6_UNORM_PACK16);

			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R10X6_G10X6_UNORM_2PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R10X6_G10X6_B10X6_A10X6_UNORM_4PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R12X4_UNORM_PACK16);
			GetFourthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R12X4_G12X4_UNORM_2PACK16);
		}

		{
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R12X4_G12X4_B12X4_A12X4_UNORM_4PACK16);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_SFLOAT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_SINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_SNORM);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_SSCALED);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_UINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_UNORM);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R16_USCALED);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_SFLOAT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_SINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_SNORM);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_SSCALED);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_UINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_UNORM);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG16_USCALED);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB16_SFLOAT);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB16_SINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB16_SNORM);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB16_UINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB16_UNORM);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_SFLOAT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_SINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_SNORM);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_SSCALED);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_UINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_UNORM);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA16_USCALED);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R32_SFLOAT);

			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R32_SINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R32_UINT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R32_SFLOAT);
			GetFifthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R32_SINT);
		}

		{
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG32_UINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB32_SFLOAT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB32_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB32_UINT);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA32_SFLOAT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA32_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA32_UINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG4_UNORM_PACK8);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA4_UNORM_PACK16);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB5_A1_UNORM_PACK16);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R5_G6_B5_UNORM_PACK16);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R64_SFLOAT);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R64_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R64_UINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG64_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG64_UINT);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA64_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA64_UINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_SNORM);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_SRGB);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_SSCALED);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_UINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_UNORM);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_R8_USCALED);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_SINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_SNORM);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_SRGB);

			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_SSCALED);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_UINT);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_UNORM);
			GetSixthSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RG8_USCALED);
		}

		{
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB8_SINT);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB8_SNORM);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB8_SRGB);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB8_UINT);

			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGB8_UNORM);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_SINT);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_SNORM);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_SRGB);

			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_SSCALED);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_UINT);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_UNORM);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_RGBA8_USCALED);

			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_S8_UINT);
			GetSeventhSetsFormatsSupportedFeatures(ret, VulkanSimplified::DATA_FORMAT_X8D24_UNORM_PACK32);
		}

		return ret;
	}

	void PhysicalDeviceDataInternal::GetFirstSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatFirstFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.firstSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.firstSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.firstSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.firstSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.firstSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.firstSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.firstSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.firstSet |= flagSetBit;
		}
	}

	void PhysicalDeviceDataInternal::GetSecondSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatSecondFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.secondSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.secondSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.secondSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.secondSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.secondSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.secondSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.secondSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.secondSet |= flagSetBit;
		}
	}

	void PhysicalDeviceDataInternal::GetThirdSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatThirdFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.thirdSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.thirdSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.thirdSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.thirdSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.thirdSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.thirdSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.thirdSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.thirdSet |= flagSetBit;
		}
	}

	void PhysicalDeviceDataInternal::GetFourthSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatFourthFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.fourthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.fourthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.fourthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.fourthSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.fourthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.fourthSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.fourthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.fourthSet |= flagSetBit;
		}
	}

	void PhysicalDeviceDataInternal::GetFifthSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatFifthFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.fifthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.fifthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.fifthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.fifthSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.fifthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.fifthSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.fifthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.fifthSet |= flagSetBit;
		}
	}

	void PhysicalDeviceDataInternal::GetSixthSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatSixthFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.sixthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.sixthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.sixthSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.sixthSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.sixthSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.sixthSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.sixthSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.sixthSet |= flagSetBit;
		}
	}

	void PhysicalDeviceDataInternal::GetSeventhSetsFormatsSupportedFeatures(VulkanSimplified::FormatsSupportedFeatures& formatsSupportedFeatures,
		VulkanSimplified::DataFormatSeventhFlagSetBits flagSetBit) const
	{
		VkFormatProperties formatProperties{};
		VkFormat format = TranslateDataFormatToVkFormat(flagSetBit);

		vkGetPhysicalDeviceFormatProperties(_device, format, &formatProperties);

		{
			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.uniformTexelBuffer.seventhSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBuffer.seventhSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.storageTexelBufferAtomic.seventhSet |= flagSetBit;

			if ((formatProperties.bufferFeatures & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) == VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
				formatsSupportedFeatures.formatFeaturesBufferSupport.vertexBuffer.seventhSet |= flagSetBit;
		}

		{
			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImage.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImage.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.storageImageAtomic.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachment.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.colorAttachmentBlend.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.depthStencilAttachment.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitSrc.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.blitDst.seventhSet |= flagSetBit;

			if ((formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesLinearImageSupport.sampledImageFilterLinear.seventhSet |= flagSetBit;
		}

		{
			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImage.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImage.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) == VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.storageImageAtomic.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachment.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) == VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.colorAttachmentBlend.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.depthStencilAttachment.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT) == VK_FORMAT_FEATURE_BLIT_SRC_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitSrc.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT) == VK_FORMAT_FEATURE_BLIT_DST_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.blitDst.seventhSet |= flagSetBit;

			if ((formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) == VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
				formatsSupportedFeatures.formatFeaturesOptimalImageSupport.sampledImageFilterLinear.seventhSet |= flagSetBit;
		}
	}

	VulkanSimplified::MemoryDataList PhysicalDeviceDataInternal::CompileAvailableMemory() const
	{
		VulkanSimplified::MemoryDataList ret;

		VkPhysicalDeviceMemoryProperties memoryProperties{};

		vkGetPhysicalDeviceMemoryProperties(_device, &memoryProperties);

		ret.heapAmount = memoryProperties.memoryHeapCount;

		for (size_t i = 0; i < memoryProperties.memoryHeapCount; i++)
		{
			const auto& data = memoryProperties.memoryHeaps[i];
			auto& heap = ret.memoryHeaps[i];

			heap.size = data.size;
			heap.properties = GetMemoryHeapProperties(data.flags);
		}

		for (uint32_t j = 0; j < memoryProperties.memoryTypeCount; j++)
		{
			const auto& data = memoryProperties.memoryTypes[j];
			auto& heap = ret.memoryHeaps[data.heapIndex];
			auto& type = heap.memoryTypes[heap.memoryTypeAmount];

			type.memoryIndex = j;
			type.properties = GetMemoryTypeProperties(data.propertyFlags);

			heap.memoryTypeAmount++;
		}

		return ret;
	}

	VulkanSimplified::MemoryTypeProperties PhysicalDeviceDataInternal::GetMemoryTypeProperties(VkMemoryPropertyFlags propertyFlags) const
	{
		VulkanSimplified::MemoryTypeProperties ret = 0;

		if ((propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
			ret |= VulkanSimplified::DEVICE_LOCAL;

		if ((propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
			ret |= VulkanSimplified::HOST_VISIBLE;

		if ((propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
			ret |= VulkanSimplified::HOST_COHERENT;

		if ((propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) == VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
			ret |= VulkanSimplified::HOST_CACHED;

		if ((propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) == VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
			ret |= VulkanSimplified::LAZYLY_ALLOCATED;

		if ((propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT) == VK_MEMORY_PROPERTY_PROTECTED_BIT)
			ret |= VulkanSimplified::PROTECTED;

		return ret;
	}

	VulkanSimplified::MemoryHeapProperties PhysicalDeviceDataInternal::GetMemoryHeapProperties(VkMemoryHeapFlags propertyFlags) const
	{
		VulkanSimplified::MemoryHeapProperties ret = 0;

		if ((propertyFlags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
			ret |= VulkanSimplified::DEVICE_LOCAL_HEAP;

		if ((propertyFlags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT) == VK_MEMORY_HEAP_MULTI_INSTANCE_BIT)
			ret |= VulkanSimplified::MULTI_INSTANCE_HEAP;

		return ret;
	}

	std::optional<VulkanSimplified::SurfaceSupportData> PhysicalDeviceDataInternal::CompileSurfaceSupport(VkSurfaceKHR testSurface) const
	{
		std::optional<VulkanSimplified::SurfaceSupportData> ret;

		if (testSurface != VK_NULL_HANDLE)
		{
			ret.emplace();
			auto& data = ret.value();

			VkSurfaceCapabilitiesKHR surfaceCapabilities{};

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, testSurface, &surfaceCapabilities);

			data.minWidth = surfaceCapabilities.minImageExtent.width;
			data.minHeight = surfaceCapabilities.minImageExtent.height;

			data.maxWidth = surfaceCapabilities.maxImageExtent.width;
			data.maxHeight = surfaceCapabilities.maxImageExtent.height;

			data.minImageCount = surfaceCapabilities.minImageCount;
			data.maxImageCount = surfaceCapabilities.maxImageCount;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) == VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_TRANSFER_SRC;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) == VK_IMAGE_USAGE_TRANSFER_DST_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_TRANSFER_DST;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_SAMPLED_BIT) == VK_IMAGE_USAGE_SAMPLED_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_SAMPLED;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_STORAGE_BIT) == VK_IMAGE_USAGE_STORAGE_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_STORAGE;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) == VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_COLOR_ATTACHMENT;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT) == VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_TRANSIENT_ATTACHMENT;

			if ((surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT) == VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
				data.surfaceUsageFlags |= VulkanSimplified::IMAGE_USAGE_INPUT_ATTACHMENT;

			std::vector<VkPresentModeKHR> surfacePresentModes;
			uint32_t size = 0;

			vkGetPhysicalDeviceSurfacePresentModesKHR(_device, testSurface, &size, nullptr);

			if (size > 0)
			{
				surfacePresentModes.resize(size);
				vkGetPhysicalDeviceSurfacePresentModesKHR(_device, testSurface, &size, surfacePresentModes.data());

				for (auto& presentMode : surfacePresentModes)
				{
					if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
						data.surfacePresentModes |= VulkanSimplified::PRESENT_MODE_IMMEDIATE;

					if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
						data.surfacePresentModes |= VulkanSimplified::PRESENT_MODE_MAILBOX;

					if (presentMode == VK_PRESENT_MODE_FIFO_KHR)
						data.surfacePresentModes |= VulkanSimplified::PRESENT_MODE_FIFO_STRICT;

					if (presentMode == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
						data.surfacePresentModes |= VulkanSimplified::PRESENT_MODE_FIFO_RELAXED;
				}
			}

			size = 0;

			vkGetPhysicalDeviceSurfaceFormatsKHR(_device, testSurface, &size, nullptr);

			std::vector<VkSurfaceFormatKHR> supportedSwapchainFormats;

			if (size > 0)
			{
				supportedSwapchainFormats.resize(size);

				vkGetPhysicalDeviceSurfaceFormatsKHR(_device, testSurface, &size, supportedSwapchainFormats.data());

				for (auto& formatData : supportedSwapchainFormats)
				{
					if (formatData.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
					{
						auto& srgb = data.surfaceSupportedSwapchainFormats.srgbNonlinearColorspace;

						if (formatData.format == VK_FORMAT_A1R5G5B5_UNORM_PACK16)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_A1_RGB5_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_A2B10G10R10_UNORM_PACK32)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_A2_BGR10_UNORM_PACK32;

						if (formatData.format == VK_FORMAT_A2R10G10B10_UNORM_PACK32)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_A2_RGB10_UNORM_PACK32;

						if (formatData.format == VK_FORMAT_A8B8G8R8_SNORM_PACK32)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_ABGR8_SNORM_PACK32;

						if (formatData.format == VK_FORMAT_A8B8G8R8_SRGB_PACK32)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_ABGR8_SRGB_PACK32;

						if (formatData.format == VK_FORMAT_A8B8G8R8_UNORM_PACK32)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_ABGR8_UNORM_PACK32;

						if (formatData.format == VK_FORMAT_B10G11R11_UFLOAT_PACK32)
							srgb.secondSet |= VulkanSimplified::DATA_FORMAT_B10_GR11_UFLOAT_PACK32;

						if (formatData.format == VK_FORMAT_B4G4R4A4_UNORM_PACK16)
							srgb.secondSet |= VulkanSimplified::DATA_FORMAT_BGRA4_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_B5G5R5A1_UNORM_PACK16)
							srgb.secondSet |= VulkanSimplified::DATA_FORMAT_BGR5_A1_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_B5G6R5_UNORM_PACK16)
							srgb.secondSet |= VulkanSimplified::DATA_FORMAT_B5_G6_R5_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_B8G8R8A8_SNORM)
							srgb.secondSet |= VulkanSimplified::DATA_FORMAT_BGRA8_SNORM;

						if (formatData.format == VK_FORMAT_B8G8R8A8_SRGB)
							srgb.secondSet |= VulkanSimplified::DATA_FORMAT_BGRA8_SRGB;

						if (formatData.format == VK_FORMAT_B8G8R8A8_UNORM)
							srgb.thirdSet |= VulkanSimplified::DATA_FORMAT_BGRA8_UNORM;

						if (formatData.format == VK_FORMAT_R16G16B16A16_SFLOAT)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_RGBA16_SFLOAT;

						if (formatData.format == VK_FORMAT_R16G16B16A16_SNORM)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_RGBA16_SNORM;

						if (formatData.format == VK_FORMAT_B8G8R8A8_UNORM)
							srgb.fifthSet |= VulkanSimplified::DATA_FORMAT_RGBA16_UNORM;

						if (formatData.format == VK_FORMAT_R4G4B4A4_UNORM_PACK16)
							srgb.sixthSet |= VulkanSimplified::DATA_FORMAT_RGBA4_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_R5G5B5A1_UNORM_PACK16)
							srgb.sixthSet |= VulkanSimplified::DATA_FORMAT_RGB5_A1_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_R5G6B5_UNORM_PACK16)
							srgb.sixthSet |= VulkanSimplified::DATA_FORMAT_R5_G6_B5_UNORM_PACK16;

						if (formatData.format == VK_FORMAT_R8_UNORM)
							srgb.sixthSet |= VulkanSimplified::DATA_FORMAT_R8_UNORM;

						if (formatData.format == VK_FORMAT_R8G8B8A8_SNORM)
							srgb.seventhSet |= VulkanSimplified::DATA_FORMAT_RGBA8_SNORM;

						if (formatData.format == VK_FORMAT_R8G8B8A8_SRGB)
							srgb.seventhSet |= VulkanSimplified::DATA_FORMAT_RGBA8_SRGB;

						if (formatData.format == VK_FORMAT_R8G8B8A8_UNORM)
							srgb.seventhSet |= VulkanSimplified::DATA_FORMAT_RGBA8_UNORM;
					}
				}
			}
		}

		return ret;
	}

	void PhysicalDeviceDataInternal::AddToConstCharVector(std::vector<const char*>& vector, const char* addedObject)
	{
		size_t vectorsNewCapacity = vector.capacity() << 1;

		if (vectorsNewCapacity == 0)
		{
			vector.reserve(16);
		}
		else if (vector.size() == vector.capacity() && vectorsNewCapacity > vector.capacity() && vectorsNewCapacity <= vector.max_size())
		{
			vector.reserve(vectorsNewCapacity);
		}
		else if (vector.capacity() != vector.max_size())
		{
			vector.reserve(vector.max_size());
		}
		else
			throw std::runtime_error("PhysicalDeviceDataInternal::AddToConstCharVector Error: Program needs more than vectors max capacity!");
		
		vector.push_back(addedObject);
	}

}