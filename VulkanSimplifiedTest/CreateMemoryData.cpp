#include "pch.h"
#include "CreateMemoryData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanMemoryData.h"

#include "SwapchainSizes.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>

#include <VSImageDataLists.h>
#include <VSMemoryObjectsList.h>

#include <VSImageUsageFlags.h>
#include <VSMemoryTypeProperties.h>

void CreateMemoryData(VulkanData& data)
{
	auto device = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto imageList = device.GetImageDataLists();
	auto memoryList = device.GetMemoryObjectsList();

	auto format = data.instanceDependentData->supportedFormat;

	data.memoryData = std::make_unique<VulkanMemoryData>();
	auto& memData = *data.memoryData;
	
	memData.colorRenderTargetImages.reserve(framesInFlight);
	memData.colorRenderTargetImageViews.reserve(framesInFlight);

	constexpr VulkanSimplified::ImageUsageFlags usageFlags = VulkanSimplified::ImageUsageFlagBits::IMAGE_USAGE_COLOR_ATTACHMENT |
		VulkanSimplified::ImageUsageFlagBits::IMAGE_USAGE_TRANSFER_SRC;

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		memData.colorRenderTargetImages.push_back(imageList.AddColorRenderTargetImage(width, height, format, usageFlags, {}, false, 1, framesInFlight));
	}

	size_t allocationSize = imageList.GetColorRenderTargetImageSize(memData.colorRenderTargetImages.back()) * framesInFlight;
	uint32_t memoryTypeMask = imageList.GetColorRenderTargetImageMemoryTypeMask(memData.colorRenderTargetImages.back());

	std::vector<VulkanSimplified::MemoryTypeProperties> acceptableMemoryTypes;
	acceptableMemoryTypes.reserve(7);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);

	memData.imageMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 1);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		imageList.BindColorRenderTargetImage(memData.colorRenderTargetImages[i], memData.imageMemoryAllocation);
		memData.colorRenderTargetImageViews.push_back(imageList.AddColorRenderTargetImageView(memData.colorRenderTargetImages[i]));
	}
}
