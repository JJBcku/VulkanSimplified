#include "pch.h"
#include "CreateInstanceDependentData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"

#include <Miscellaneous/Bool64.h>

#include <VSDevicesSupportedFormats.h>
#include <VSDeviceSwapchainSupportData.h>

#include <VSMain.h>
#include <VSInstance.h>

#include <VSCompositeAlphaFlags.h>
#include <VSImageUsageFlags.h>
#include <VSSurfacePresentModes.h>
#include <VSSurfaceTransformFlags.h>

#include <VSPhysicalDeviceData.h>
#include <VSDeviceVulkan10Properties.h>
#include <VSDeviceVulkan10FeatureFlags.h>
#include <VSDeviceExtensionPacksList.h>
#include <VSDeviceQueueFamilyData.h>
#include <VSLogicalDeviceCreateInfo.h>

#include "VSDeviceInitialCapacitiesList.h"

static bool CheckFormatSupport(const VS::FormatsSupportedImageFeaturesList& supportedImageFormats,
	const VS::SurfaceSupportedColorspaceFormatsLists& surfaceColorspace, const VS::DataFormatSetIndependentID& formatID)
{
	return CheckFormatSupport(supportedImageFormats.blitDst, formatID) && CheckFormatSupport(surfaceColorspace.srgbNonlinearColorspace, formatID);
}

static size_t ChooseGPU(VS::Instance& instance)
{
	size_t ret = 0;

	size_t gpuAmount = instance.GetAvailableDevicesCount();

	uint32_t bestDiscreteGpuApi = 0;
	std::optional<size_t> bestDiscreteGpu;

	uint32_t bestIntegratedGpuApi = 0;
	std::optional<size_t> bestIntegratedGpu;

	uint32_t bestVirtualGpuApi = 0;
	std::optional<size_t> bestVirtualGpu;

	uint32_t bestCpuApi = 0;
	std::optional<size_t> bestCpu;

	for (size_t i = 0; i < gpuAmount; i++)
	{
		auto deviceInfo = instance.GetPhysicalDeviceData(i);
		auto& deviceProperties = deviceInfo.GetVulkan10Properties();

		auto& deviceExtensionPacks = deviceInfo.GetDeviceExtensionPacks();

		if (!deviceExtensionPacks.swapchainBase)
			continue;

		auto& deviceSurfaceSupportOptional = deviceInfo.GetSurfaceSupport();

		if (!deviceSurfaceSupportOptional.has_value())
			continue;

		auto& deviceSurfaceSupport = deviceSurfaceSupportOptional.value();

		if ((deviceSurfaceSupport.surfaceUsageFlags & VS::IMAGE_USAGE_TRANSFER_DST) != VS::IMAGE_USAGE_TRANSFER_DST)
			continue;

		if ((deviceSurfaceSupport.surfaceSupportedCompositeAlphaModes & VS::COMPOSITE_ALPHA_OPAQUE) != VS::COMPOSITE_ALPHA_OPAQUE)
			continue;

		if ((deviceSurfaceSupport.surfacePresentModes & VS::PRESENT_MODE_FIFO_STRICT) != VS::PRESENT_MODE_FIFO_STRICT)
			continue;

		if ((deviceSurfaceSupport.surfaceSupportedTransformations & VS::SURFACE_TRASFORM_IDENTITY) != VS::SURFACE_TRASFORM_IDENTITY)
			continue;

		if (deviceSurfaceSupport.surfaceDefaultTransformation != VS::SURFACE_TRASFORM_IDENTITY)
			continue;

		auto& surfaceSupport = deviceSurfaceSupport.surfaceSupportedSwapchainFormats;
		auto& supportedFormats = deviceInfo.GetFormatsSupportedFeatures();
		auto& imageSupport = supportedFormats.formatFeaturesOptimalImageSupport;

		bool bgraSupported = CheckFormatSupport(imageSupport, surfaceSupport, VS::DATA_FORMAT_BGRA8_UNORM) &&
			CheckFormatSupport(imageSupport.colorAttachment, VS::DATA_FORMAT_BGRA8_UNORM);
		bool rgbaSupported = CheckFormatSupport(imageSupport, surfaceSupport, VS::DATA_FORMAT_RGBA8_UNORM) &&
			CheckFormatSupport(imageSupport.colorAttachment, VS::DATA_FORMAT_RGBA8_UNORM);

		if (!bgraSupported && !rgbaSupported)
			continue;

		if (!CheckFormatSupport(supportedFormats.formatFeaturesBufferSupport.vertexBuffer, VS::DATA_FORMAT_RGBA32_SFLOAT))
			continue;

		bool depthSupported = CheckFormatSupport(imageSupport.depthStencilAttachment, VS::DATA_FORMAT_D32_SFLOAT_S8_UINT) ||
			CheckFormatSupport(imageSupport.depthStencilAttachment, VS::DATA_FORMAT_D24_UNORM_S8_UINT) ||
			CheckFormatSupport(imageSupport.depthStencilAttachment, VS::DATA_FORMAT_D16_UNORM_S8_UINT);

		if (!depthSupported)
			continue;

		switch (deviceProperties.deviceType)
		{
		case VS::DeviceType::OTHER:
			break;
		case VS::DeviceType::INTERGRATED_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestIntegratedGpuApi)
			{
				bestIntegratedGpu = i;
				bestIntegratedGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case VS::DeviceType::DISCRETE_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestDiscreteGpuApi)
			{
				bestDiscreteGpu = i;
				bestDiscreteGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case VS::DeviceType::VIRTUAL_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestVirtualGpuApi)
			{
				bestVirtualGpu = i;
				bestVirtualGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case VS::DeviceType::CPU:
			if (deviceProperties.apiMaxSupportedVersion > bestCpuApi)
			{
				bestCpu = i;
				bestCpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		default:
			break;
		}
	}

	if (bestDiscreteGpu.has_value())
	{
		ret = bestDiscreteGpu.value();
	}
	else if (bestIntegratedGpu.has_value())
	{
		ret = bestIntegratedGpu.value();
	}
	else if (bestVirtualGpu.has_value())
	{
		ret = bestVirtualGpu.value();
	}
	else if (bestCpu.has_value())
	{
		ret = bestCpu.value();
	}
	else
	{
		throw std::runtime_error("Program found no suitable device!");
	}

	return ret;
}

static std::pair<uint32_t, bool> PickGraphicQueueFamily(VS::PhysicalDeviceData& physicalDevice)
{
	std::pair<uint32_t, bool> choosenFamily = { std::numeric_limits<uint32_t>::max(), false };

	auto& queueData = physicalDevice.GetVulkanQueueFamiliesData();

	std::optional<uint32_t> bestNonVideoGraphicQueueFamilyPresenting;
	uint32_t bestNonVideoGraphicQueueFamilyGranularityPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestNonVideoGraphicQueueFamilyTimestampPresenting = 0;

	std::optional<uint32_t> bestNonVideoGraphicQueueFamilyNonPresenting;
	uint32_t bestNonVideoGraphicQueueFamilyGranularityNonPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestNonVideoGraphicQueueFamilyTimestampNonPresenting = 0;

	std::optional<uint32_t> bestVideoGraphicQueueFamilyPresenting;
	uint32_t bestVideoGraphicQueueFamilyGranularityPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestVideoGraphicQueueFamilyTimestampPresenting = 0;

	std::optional<uint32_t> bestVideoGraphicQueueFamilyNonPresenting;
	uint32_t bestVideoGraphicQueueFamilyGranularityNonPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestVideoGraphicQueueFamilyTimestampNonPresenting = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & VS::QUEUE_TYPE_GRAPHICS) != VS::QUEUE_TYPE_GRAPHICS)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & VS::QUEUE_TYPE_VIDEO_DECODE) != VS::QUEUE_TYPE_VIDEO_DECODE &&
			(family.queueTypes & VS::QUEUE_TYPE_VIDEO_ENCODE) != VS::QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (queueData[i].presentationSupport == Misc::BOOL64_TRUE)
			{
				if (bestNonVideoGraphicQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoGraphicQueueFamilyGranularityPresenting == biggestGranularity && bestNonVideoGraphicQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoGraphicQueueFamilyPresenting = static_cast<uint32_t>(i);
					bestNonVideoGraphicQueueFamilyGranularityPresenting = biggestGranularity;
					bestNonVideoGraphicQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestNonVideoGraphicQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoGraphicQueueFamilyGranularityNonPresenting == biggestGranularity && bestNonVideoGraphicQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoGraphicQueueFamilyNonPresenting = static_cast<uint32_t>(i);
					bestNonVideoGraphicQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestNonVideoGraphicQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
		else
		{
			if (queueData[i].presentationSupport == Misc::BOOL64_TRUE)
			{
				if (bestVideoGraphicQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoGraphicQueueFamilyGranularityPresenting == biggestGranularity && bestVideoGraphicQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoGraphicQueueFamilyPresenting = static_cast<uint32_t>(i);
					bestVideoGraphicQueueFamilyGranularityPresenting = biggestGranularity;
					bestVideoGraphicQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestVideoGraphicQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoGraphicQueueFamilyGranularityNonPresenting == biggestGranularity && bestVideoGraphicQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoGraphicQueueFamilyNonPresenting = static_cast<uint32_t>(i);
					bestVideoGraphicQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestVideoGraphicQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
	}

	if (bestNonVideoGraphicQueueFamilyPresenting.has_value())
	{
		choosenFamily.first = bestNonVideoGraphicQueueFamilyPresenting.value();
		choosenFamily.second = true;
	}
	else if (bestNonVideoGraphicQueueFamilyNonPresenting.has_value())
	{
		choosenFamily.first = bestNonVideoGraphicQueueFamilyNonPresenting.value();
		choosenFamily.second = false;
	}
	else if (bestVideoGraphicQueueFamilyPresenting.has_value())
	{
		choosenFamily.first = bestVideoGraphicQueueFamilyPresenting.value();
		choosenFamily.second = true;
	}
	else if (bestVideoGraphicQueueFamilyNonPresenting.has_value())
	{
		choosenFamily.first = bestVideoGraphicQueueFamilyNonPresenting.value();
		choosenFamily.second = false;
	}
	else
	{
		throw std::runtime_error("PickGraphicQueueFamily Error: Program failed to find a graphics queue!");
	}

	return choosenFamily;
}

static std::optional<std::pair<uint32_t, bool>> TryToFindTransferOnlyQueueFamily(const VS::PhysicalDeviceData& physicalDevice)
{
	std::optional<std::pair<uint32_t, bool>> choosenFamily;

	auto& queueData = physicalDevice.GetVulkanQueueFamiliesData();

	std::optional<uint32_t> bestNonVideoTransferOnlyQueueFamilyPresenting;
	uint32_t bestNonVideoTransferOnlyQueueFamilyGranularityPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestNonVideoTransferOnlyQueueFamilyTimestampPresenting = 0;

	std::optional<uint32_t> bestNonVideoTransferOnlyQueueFamilyNonPresenting;
	uint32_t bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting = 0;

	std::optional<uint32_t> bestVideoTransferOnlyQueueFamilyPresenting;
	uint32_t bestVideoTransferOnlyQueueFamilyGranularityPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestVideoTransferOnlyQueueFamilyTimestampPresenting = 0;

	std::optional<uint32_t> bestVideoTransferOnlyQueueFamilyNonPresenting;
	uint32_t bestVideoTransferOnlyQueueFamilyGranularityNonPresenting = std::numeric_limits<uint32_t>::max();
	uint32_t bestVideoTransferOnlyQueueFamilyTimestampNonPresenting = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & VS::QUEUE_TYPE_GRAPHICS) == VS::QUEUE_TYPE_GRAPHICS ||
			(family.queueTypes & VS::QUEUE_TYPE_COMPUTE) == VS::QUEUE_TYPE_COMPUTE)
			continue;

		if ((family.queueTypes & VS::QUEUE_TYPE_TRANSFER) != VS::QUEUE_TYPE_TRANSFER)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & VS::QUEUE_TYPE_VIDEO_DECODE) != VS::QUEUE_TYPE_VIDEO_DECODE &&
			(family.queueTypes & VS::QUEUE_TYPE_VIDEO_ENCODE) != VS::QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (queueData[i].presentationSupport == Misc::BOOL64_TRUE)
			{
				if (bestNonVideoTransferOnlyQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoTransferOnlyQueueFamilyGranularityPresenting == biggestGranularity && bestNonVideoTransferOnlyQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoTransferOnlyQueueFamilyPresenting = static_cast<uint32_t>(i);
					bestNonVideoTransferOnlyQueueFamilyGranularityPresenting = biggestGranularity;
					bestNonVideoTransferOnlyQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting == biggestGranularity && bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestNonVideoTransferOnlyQueueFamilyNonPresenting = static_cast<uint32_t>(i);
					bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
		else
		{
			if (queueData[i].presentationSupport == Misc::BOOL64_TRUE)
			{
				if (bestVideoTransferOnlyQueueFamilyGranularityPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoTransferOnlyQueueFamilyGranularityPresenting == biggestGranularity && bestVideoTransferOnlyQueueFamilyTimestampPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoTransferOnlyQueueFamilyPresenting = static_cast<uint32_t>(i);
					bestVideoTransferOnlyQueueFamilyGranularityPresenting = biggestGranularity;
					bestVideoTransferOnlyQueueFamilyTimestampPresenting = family.timespampValidBits;
				}
			}
			else
			{
				if (bestVideoTransferOnlyQueueFamilyGranularityNonPresenting > biggestGranularity)
				{
					better = true;
				}
				else if (bestVideoTransferOnlyQueueFamilyGranularityNonPresenting == biggestGranularity && bestVideoTransferOnlyQueueFamilyTimestampNonPresenting < family.timespampValidBits)
				{
					better = true;
				}

				if (better)
				{
					bestVideoTransferOnlyQueueFamilyNonPresenting = static_cast<uint32_t>(i);
					bestVideoTransferOnlyQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestVideoTransferOnlyQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
	}

	if (bestNonVideoTransferOnlyQueueFamilyPresenting.has_value())
	{
		choosenFamily = { bestNonVideoTransferOnlyQueueFamilyPresenting.value(), true };
	}
	else if (bestNonVideoTransferOnlyQueueFamilyNonPresenting.has_value())
	{
		choosenFamily = { bestNonVideoTransferOnlyQueueFamilyNonPresenting.value(), false };
	}
	else if (bestVideoTransferOnlyQueueFamilyPresenting.has_value())
	{
		choosenFamily = { bestVideoTransferOnlyQueueFamilyPresenting.value(), true };
	}
	else if (bestVideoTransferOnlyQueueFamilyNonPresenting.has_value())
	{
		choosenFamily = { bestVideoTransferOnlyQueueFamilyNonPresenting.value(), false };
	}

	return choosenFamily;
}

static uint32_t FindPresentingQueueFamily(const std::vector<VS::QueueFamilyData> queueData)
{
	uint32_t ret = std::numeric_limits<uint32_t>::max();

	for (size_t i = 0; i < queueData.size(); i++)
	{
		if (queueData[i].presentationSupport == Misc::BOOL64_TRUE)
		{
			ret = static_cast<uint32_t>(i);
			break;
		}
	}

	if (ret == std::numeric_limits<uint32_t>::max())
		throw std::runtime_error("PickGraphicQueueFamily Error: Program failed to find a present queue!");

	return ret;
}

static VS::ImageSampleFlagBits GetMaxSamples(VS::ImageSampleFlags samples)
{
	using VS::ImageSampleFlagBits;

	ImageSampleFlagBits ret = ImageSampleFlagBits::SAMPLE_1;

	if ((samples & ImageSampleFlagBits::SAMPLE_2) == ImageSampleFlagBits::SAMPLE_2)
		ret = ImageSampleFlagBits::SAMPLE_2;

	if ((samples & ImageSampleFlagBits::SAMPLE_4) == ImageSampleFlagBits::SAMPLE_4)
		ret = ImageSampleFlagBits::SAMPLE_4;

	if ((samples & ImageSampleFlagBits::SAMPLE_8) == ImageSampleFlagBits::SAMPLE_8)
		ret = ImageSampleFlagBits::SAMPLE_8;

	if ((samples & ImageSampleFlagBits::SAMPLE_16) == ImageSampleFlagBits::SAMPLE_16)
		ret = ImageSampleFlagBits::SAMPLE_16;

	if ((samples & ImageSampleFlagBits::SAMPLE_32) == ImageSampleFlagBits::SAMPLE_32)
		ret = ImageSampleFlagBits::SAMPLE_32;

	if ((samples & ImageSampleFlagBits::SAMPLE_64) == ImageSampleFlagBits::SAMPLE_64)
		ret = ImageSampleFlagBits::SAMPLE_64;

	return ret;
}

void CreateInstanceDependentData(VulkanData& data)
{
	auto& main = *data.basicData->vsmain;
	auto instance = main.GetInstance();

	data.instanceDependentData = std::make_unique<VulkanInstanceDependentData>();
	auto& instanceData = *data.instanceDependentData;

	instanceData.physicalDevicesIndex = ChooseGPU(instance);
	auto physicalDevice = instance.GetPhysicalDeviceData(instanceData.physicalDevicesIndex);
	auto& deviceProperties = physicalDevice.GetVulkan10Properties();
	auto& deviceFeatures = physicalDevice.GetVulkan10Features();

	auto deviceInfo = instance.GetPhysicalDeviceData(instanceData.physicalDevicesIndex);
	auto& deviceSurfaceSupport = deviceInfo.GetSurfaceSupport().value();

	auto& surfaceSupport = deviceSurfaceSupport.surfaceSupportedSwapchainFormats;
	auto& supportedFormats = deviceInfo.GetFormatsSupportedFeatures();
	auto& imageSupport = supportedFormats.formatFeaturesOptimalImageSupport;

	bool bgraSupported = CheckFormatSupport(imageSupport, surfaceSupport, VS::DATA_FORMAT_BGRA8_UNORM) &&
		CheckFormatSupport(imageSupport.colorAttachment, VS::DATA_FORMAT_BGRA8_UNORM);

	if (bgraSupported)
		instanceData.supportedColorFormat = VS::DATA_FORMAT_BGRA8_UNORM;
	else
		instanceData.supportedColorFormat = VS::DATA_FORMAT_RGBA8_UNORM;

	if (CheckFormatSupport(imageSupport.depthStencilAttachment, VS::DATA_FORMAT_D32_SFLOAT_S8_UINT))
	{
		instanceData.supportedDepthFormat = VS::DATA_FORMAT_D32_SFLOAT_S8_UINT;
	}
	else if (CheckFormatSupport(imageSupport.depthStencilAttachment, VS::DATA_FORMAT_D24_UNORM_S8_UINT))
	{
		instanceData.supportedDepthFormat = VS::DATA_FORMAT_D24_UNORM_S8_UINT;
	}
	else
	{
		instanceData.supportedDepthFormat = VS::DATA_FORMAT_D16_UNORM_S8_UINT;
	}

	instanceData.minSwapchainImageAmount = deviceSurfaceSupport.minImageCount;
	instanceData.maxSwapchainImageAmount = deviceSurfaceSupport.maxImageCount;

	instanceData.maxSamples = GetMaxSamples(deviceProperties.limits.framebufferLimits.framebufferColorSampleCounts &
		deviceProperties.limits.framebufferLimits.framebufferColorSampleCounts);

	VS::LogicalDeviceCreationData deviceCreationData;
	deviceCreationData.physicalGPUIndex = instanceData.physicalDevicesIndex;
	deviceCreationData.queuesCreationInfo.reserve(3);

	VS::QueueCreationData queueCreationData;
	queueCreationData.queuesPriorities.push_back(std::numeric_limits<uint16_t>::max());

	auto graphicQueueFamily = PickGraphicQueueFamily(physicalDevice);
	queueCreationData.queuesFamily = graphicQueueFamily.first;
	instanceData.graphicsQueueIndex = deviceCreationData.queuesCreationInfo.size();
	instanceData.graphicsQueueFamily = queueCreationData.queuesFamily;
	deviceCreationData.queuesCreationInfo.push_back(queueCreationData);

	if ((deviceFeatures & VS::DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY) == VS::DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY)
	{
		instanceData.maxAnisotropy = deviceProperties.limits.maxSamplerAnisotropy;
		deviceCreationData.vulkan10EnabledFeatures |= VS::DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY;
	}
	else
	{
		instanceData.maxAnisotropy = 0.0f;
	}

	if ((deviceFeatures & VS::DEVICE_VULKAN10_FEATURE_SAMPLE_RATE_SHADING) == VS::DEVICE_VULKAN10_FEATURE_SAMPLE_RATE_SHADING)
	{
		instanceData.sampleShadingRate = std::numeric_limits<uint32_t>::max();
		deviceCreationData.vulkan10EnabledFeatures |= VS::DEVICE_VULKAN10_FEATURE_SAMPLE_RATE_SHADING;
	}

	auto transferOnlyFamily = TryToFindTransferOnlyQueueFamily(physicalDevice);
	if (transferOnlyFamily.has_value())
	{
		queueCreationData.queuesFamily = transferOnlyFamily.value().first;
		instanceData.transferOnlyQueueIndex = deviceCreationData.queuesCreationInfo.size();
		instanceData.transferOnlyQueueFamily = queueCreationData.queuesFamily;
		deviceCreationData.queuesCreationInfo.push_back(queueCreationData);
	}

	if (!graphicQueueFamily.second && (!transferOnlyFamily.has_value() || !transferOnlyFamily.value().second))
	{
		auto presentingQueueFamily = FindPresentingQueueFamily(physicalDevice.GetVulkanQueueFamiliesData());
		queueCreationData.queuesFamily = presentingQueueFamily;
		instanceData.presentingQueueIndex = deviceCreationData.queuesCreationInfo.size();
		instanceData.presentingQueueFamily = queueCreationData.queuesFamily;
		deviceCreationData.queuesCreationInfo.push_back(queueCreationData);
	}
	else if (!graphicQueueFamily.second)
	{
		instanceData.presentingQueueIndex = instanceData.transferOnlyQueueIndex.value();
		instanceData.presentingQueueFamily = instanceData.transferOnlyQueueFamily.value();
	}

	deviceCreationData.requestedExtensionPacks.swapchainBase = true;

	instance.CreateLogicalDevice(deviceCreationData, {});
}
