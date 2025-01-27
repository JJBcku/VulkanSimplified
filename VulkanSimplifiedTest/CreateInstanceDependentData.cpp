#include "pch.h"
#include "CreateInstanceDependentData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceData.h"

#include <VSDevicesSupportedFormats.h>
#include <VSDeviceSwapchainSupportData.h>

#include <VSMain.h>
#include <VSInstance.h>

#include <VSPhysicalDeviceData.h>
#include <VSDeviceVulkan10Properties.h>
#include <VSDeviceExtensionPacksList.h>
#include <VSDeviceQueueFamilyData.h>
#include <VSLogicalDeviceCreateInfo.h>

#include "VSDeviceInitialCapacitiesList.h"

static bool CheckFormatSupport(const VulkanSimplified::FormatsSupportedImageFeaturesList& supportedImageFormats,
	const VulkanSimplified::SurfaceSupportedColorspaceFormatsLists& surfaceColorspace, const VulkanSimplified::DataFormatSetIndependentID& formatID)
{
	return CheckFormatSupport(supportedImageFormats.blitDst, formatID) && CheckFormatSupport(surfaceColorspace.srgbNonlinearColorspace, formatID);
}

static size_t ChooseGPU(VulkanSimplified::Instance& instance)
{
	size_t ret = 0;

	size_t gpuAmount = instance.GetAvailableDevicesCount();

	std::uint32_t bestDiscreteGpuApi = 0;
	std::optional<size_t> bestDiscreteGpu;

	std::uint32_t bestIntegratedGpuApi = 0;
	std::optional<size_t> bestIntegratedGpu;

	std::uint32_t bestVirtualGpuApi = 0;
	std::optional<size_t> bestVirtualGpu;

	std::uint32_t bestCpuApi = 0;
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

		if ((deviceSurfaceSupport.surfaceUsageFlags & VulkanSimplified::IMAGE_USAGE_TRANSFER_DST) != VulkanSimplified::IMAGE_USAGE_TRANSFER_DST)
			continue;

		if ((deviceSurfaceSupport.surfacePresentModes & VulkanSimplified::PRESENT_MODE_FIFO_STRICT) != VulkanSimplified::PRESENT_MODE_FIFO_STRICT)
			continue;

		auto& surfaceSupport = deviceSurfaceSupport.surfaceSupportedSwapchainFormats;
		auto& supportedFormats = deviceInfo.GetFormatsSupportedFeatures();
		auto& imageSupport = supportedFormats.formatFeaturesOptimalImageSupport;

		bool bgraSupported = CheckFormatSupport(imageSupport, surfaceSupport, VulkanSimplified::DATA_FORMAT_BGRA8_UNORM) &&
			CheckFormatSupport(imageSupport.colorAttachment, VulkanSimplified::DATA_FORMAT_BGRA8_UNORM);
		bool rgbaSupported = CheckFormatSupport(imageSupport, surfaceSupport, VulkanSimplified::DATA_FORMAT_RGBA8_UNORM) &&
			CheckFormatSupport(imageSupport.colorAttachment, VulkanSimplified::DATA_FORMAT_RGBA8_UNORM);

		if (!bgraSupported && !rgbaSupported)
			continue;

		if (!CheckFormatSupport(supportedFormats.formatFeaturesBufferSupport.vertexBuffer, VulkanSimplified::DATA_FORMAT_RGBA32_SFLOAT))
			continue;

		switch (deviceProperties.deviceType)
		{
		case VulkanSimplified::DeviceType::OTHER:
			break;
		case VulkanSimplified::DeviceType::INTERGRATED_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestIntegratedGpuApi)
			{
				bestIntegratedGpu = i;
				bestIntegratedGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case VulkanSimplified::DeviceType::DISCRETE_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestDiscreteGpuApi)
			{
				bestDiscreteGpu = i;
				bestDiscreteGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case VulkanSimplified::DeviceType::VIRTUAL_GPU:
			if (deviceProperties.apiMaxSupportedVersion > bestVirtualGpuApi)
			{
				bestVirtualGpu = i;
				bestVirtualGpuApi = deviceProperties.apiMaxSupportedVersion;
			}
			break;
		case VulkanSimplified::DeviceType::CPU:
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

static std::pair<std::uint32_t, bool> PickGraphicQueueFamily(VulkanSimplified::PhysicalDeviceData& physicalDevice)
{
	std::pair<std::uint32_t, bool> choosenFamily = { std::numeric_limits<std::uint32_t>::max(), false };

	auto& queueData = physicalDevice.GetVulkanQueueFamiliesData();

	std::optional<std::uint32_t> bestNonVideoGraphicQueueFamilyPresenting;
	std::uint32_t bestNonVideoGraphicQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoGraphicQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestNonVideoGraphicQueueFamilyNonPresenting;
	std::uint32_t bestNonVideoGraphicQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoGraphicQueueFamilyTimestampNonPresenting = 0;

	std::optional<std::uint32_t> bestVideoGraphicQueueFamilyPresenting;
	std::uint32_t bestVideoGraphicQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoGraphicQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestVideoGraphicQueueFamilyNonPresenting;
	std::uint32_t bestVideoGraphicQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoGraphicQueueFamilyTimestampNonPresenting = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & VulkanSimplified::QUEUE_TYPE_GRAPHICS) != VulkanSimplified::QUEUE_TYPE_GRAPHICS)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & VulkanSimplified::QUEUE_TYPE_VIDEO_DECODE) != VulkanSimplified::QUEUE_TYPE_VIDEO_DECODE &&
			(family.queueTypes & VulkanSimplified::QUEUE_TYPE_VIDEO_ENCODE) != VulkanSimplified::QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (queueData[i].presentationSupport == VulkanSimplified::BOOL64_TRUE)
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
					bestNonVideoGraphicQueueFamilyPresenting = static_cast<std::uint32_t>(i);
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
					bestNonVideoGraphicQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
					bestNonVideoGraphicQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestNonVideoGraphicQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
		else
		{
			if (queueData[i].presentationSupport == VulkanSimplified::BOOL64_TRUE)
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
					bestVideoGraphicQueueFamilyPresenting = static_cast<std::uint32_t>(i);
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
					bestVideoGraphicQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
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

static std::optional<std::pair<std::uint32_t, bool>> TryToFindTransferOnlyQueueFamily(const VulkanSimplified::PhysicalDeviceData& physicalDevice)
{
	std::optional<std::pair<std::uint32_t, bool>> choosenFamily;

	auto& queueData = physicalDevice.GetVulkanQueueFamiliesData();

	std::optional<std::uint32_t> bestNonVideoTransferOnlyQueueFamilyPresenting;
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestNonVideoTransferOnlyQueueFamilyNonPresenting;
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting = 0;

	std::optional<std::uint32_t> bestVideoTransferOnlyQueueFamilyPresenting;
	std::uint32_t bestVideoTransferOnlyQueueFamilyGranularityPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoTransferOnlyQueueFamilyTimestampPresenting = 0;

	std::optional<std::uint32_t> bestVideoTransferOnlyQueueFamilyNonPresenting;
	std::uint32_t bestVideoTransferOnlyQueueFamilyGranularityNonPresenting = std::numeric_limits<std::uint32_t>::max();
	std::uint32_t bestVideoTransferOnlyQueueFamilyTimestampNonPresenting = 0;

	for (size_t i = 0; i < queueData.size(); i++)
	{
		auto& family = queueData[i];

		if ((family.queueTypes & VulkanSimplified::QUEUE_TYPE_GRAPHICS) == VulkanSimplified::QUEUE_TYPE_GRAPHICS ||
			(family.queueTypes & VulkanSimplified::QUEUE_TYPE_COMPUTE) == VulkanSimplified::QUEUE_TYPE_COMPUTE)
			continue;

		if ((family.queueTypes & VulkanSimplified::QUEUE_TYPE_TRANSFER) != VulkanSimplified::QUEUE_TYPE_TRANSFER)
			continue;

		bool better = false;
		auto biggestGranularity = std::max(std::max(family.minImageTransferGranularityWidth, family.minImageTransferGranularityHeight), family.minImageTransferGranularityDepth);

		if ((family.queueTypes & VulkanSimplified::QUEUE_TYPE_VIDEO_DECODE) != VulkanSimplified::QUEUE_TYPE_VIDEO_DECODE &&
			(family.queueTypes & VulkanSimplified::QUEUE_TYPE_VIDEO_ENCODE) != VulkanSimplified::QUEUE_TYPE_VIDEO_ENCODE)
		{
			if (queueData[i].presentationSupport == VulkanSimplified::BOOL64_TRUE)
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
					bestNonVideoTransferOnlyQueueFamilyPresenting = static_cast<std::uint32_t>(i);
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
					bestNonVideoTransferOnlyQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
					bestNonVideoTransferOnlyQueueFamilyGranularityNonPresenting = biggestGranularity;
					bestNonVideoTransferOnlyQueueFamilyTimestampNonPresenting = family.timespampValidBits;
				}
			}
		}
		else
		{
			if (queueData[i].presentationSupport == VulkanSimplified::BOOL64_TRUE)
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
					bestVideoTransferOnlyQueueFamilyPresenting = static_cast<std::uint32_t>(i);
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
					bestVideoTransferOnlyQueueFamilyNonPresenting = static_cast<std::uint32_t>(i);
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

static std::uint32_t FindPresentingQueueFamily(const std::vector<VulkanSimplified::QueueFamilyData> queueData)
{
	std::uint32_t ret = std::numeric_limits<std::uint32_t>::max();

	for (size_t i = 0; i < queueData.size(); i++)
	{
		if (queueData[i].presentationSupport == VulkanSimplified::BOOL64_TRUE)
		{
			ret = static_cast<std::uint32_t>(i);
			break;
		}
	}

	if (ret == std::numeric_limits<std::uint32_t>::max())
		throw std::runtime_error("PickGraphicQueueFamily Error: Program failed to find a present queue!");

	return ret;
}

void CreateInstanceDependentData(VulkanData& data)
{
	auto& main = data.basicData->vsmain.value();
	auto instance = main.GetInstance();

	data.instanceData = std::make_unique<VulkanInstanceData>();
	auto& instanceData = *data.instanceData;

	instanceData.physicalDevicesIndex = ChooseGPU(instance);
	auto physicalDevice = instance.GetPhysicalDeviceData(instanceData.physicalDevicesIndex);
	//auto& deviceProperties = physicalDevice.GetVulkan10Properties();

	VulkanSimplified::LogicalDeviceCreationData deviceCreationData;
	deviceCreationData.physicalGPUIndex = instanceData.physicalDevicesIndex;
	deviceCreationData.queuesCreationInfo.reserve(3);

	VulkanSimplified::QueueCreationData queueCreationData;
	queueCreationData.queuesPriorities.push_back(std::numeric_limits<uint16_t>::max());

	auto graphicQueueFamily = PickGraphicQueueFamily(physicalDevice);
	queueCreationData.queuesFamily = graphicQueueFamily.first;
	instanceData.graphicsQueueIndex = deviceCreationData.queuesCreationInfo.size();
	instanceData.graphicsQueueFamily = queueCreationData.queuesFamily;
	deviceCreationData.queuesCreationInfo.push_back(queueCreationData);

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
	else
	{
		if (graphicQueueFamily.second)
		{
			instanceData.presentingQueueIndex = instanceData.graphicsQueueIndex;
			instanceData.presentingQueueFamily = instanceData.graphicsQueueFamily;
		}
		else
		{
			instanceData.presentingQueueIndex = instanceData.transferOnlyQueueIndex.value();
			instanceData.presentingQueueFamily = instanceData.transferOnlyQueueFamily.value();
		}
	}

	deviceCreationData.requestedExtensionPacks.swapchainBase = true;

	instance.CreateLogicalDevice(deviceCreationData, {});
}
