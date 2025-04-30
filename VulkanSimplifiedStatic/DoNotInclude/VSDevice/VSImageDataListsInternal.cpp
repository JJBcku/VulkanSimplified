#include "VSDeviceNIpch.h"
#include "VSImageDataListsInternal.h"

#include "../../Include/VSCommon/VSDataFormatFlags.h"
#include "../../Include/VSCommon/VSImageUsageFlags.h"

#include "../../Include/VSDevice/VSImageDataListsInitialCapacities.h"

#include "VSAutoCleanupColorRenderTargetImage.h"

#include "VSDeviceCoreInternal.h"
#include "VSMemoryObjectsListInternal.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"
#include "../VSCommon/VSImageUsageFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	ImageDataListsInternal::ImageDataListsInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& renderPassData, MemoryObjectsListInternal& memoryList,
		VkDevice device, const VulkanSimplified::ImageDataListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _renderPassData(renderPassData), _memoryList(memoryList),
		_device(device), _colorRenderTargets(initialCapacities._colorRenderTargetsListInitialCapacities)
	{
	}

	ImageDataListsInternal::~ImageDataListsInternal()
	{
	}

	IDObject<AutoCleanupColorRenderTargetImage> ImageDataListsInternal::AddColorRenderTargetImage(uint32_t width, uint32_t height, VulkanSimplified::DataFormatSetIndependentID format,
		VulkanSimplified::ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		VkImage image = VK_NULL_HANDLE;
		VkImageCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

		createInfo.imageType = VK_IMAGE_TYPE_2D;
		createInfo.format = TranslateDataFormatToVkFormat(format);

		createInfo.extent.width = width;
		createInfo.extent.height = height;
		createInfo.extent.depth = 1;

		createInfo.mipLevels = 1;
		createInfo.arrayLayers = 1;
		createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

		createInfo.usage = TranslateImageUsage(usageFlags);

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingImage.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingImage);

			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(queueFamilies.size());
			createInfo.pQueueFamilyIndices = queueFamilies.data();
		}
		else
		{
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		if (preInitialized)
			createInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
		else
			createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		if (vkCreateImage(_device, &createInfo, nullptr, &image) != VK_SUCCESS)
			throw std::runtime_error("ImageDataListsInternal::AddColorRenderTargetImage Error: Program failed to create a single sampled, no mip maps, 2D image!");

		return _colorRenderTargets.AddObject(AutoCleanupColorRenderTargetImage(_device, image, width, height, createInfo.format, initialImageViewListCapacity), addOnReserving);
	}

	bool ImageDataListsInternal::RemoveColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		bool ret = _colorRenderTargets.CheckForID(imageID);

		if (!ret && throwOnIDNotFound)
			throw std::runtime_error("ImageDataListInternal::RemoveSingleSampled2DImage Error: Program tried to delete a non-existent image!");

		if (ret)
		{
			auto& imageData = _colorRenderTargets.GetObject(imageID);

			auto bindingData = imageData.GetBoundMemorySuballocation();

			ret = _colorRenderTargets.RemoveObject(imageID, true);

			if (bindingData.has_value())
				_memoryList.RemoveSuballocation(bindingData.value(), true);
		}

		return ret;
	}

	VkImage ImageDataListsInternal::GetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetImage();
	}

	VkImageView ImageDataListsInternal::GetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetImageView(viewID);
	}

	uint32_t ImageDataListsInternal::GetColorRenderTargetImageWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetWidth();
	}

	uint32_t ImageDataListsInternal::GetColorRenderTargetImageHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetHeight();
	}

	uint32_t ImageDataListsInternal::GetColorRenderTargetImageMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetImagesMemoryTypeMask();
	}

	uint64_t ImageDataListsInternal::GetColorRenderTargetImageSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetImagesSize();
	}

	uint64_t ImageDataListsInternal::GetColorRenderTargetImageRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargets.GetConstObject(imageID).GetImagesRequiredAligment();
	}

	void ImageDataListsInternal::BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, VulkanSimplified::MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		auto& imageData = _colorRenderTargets.GetObject(imageID);

		VkImage image = imageData.GetImage();
		size_t size = imageData.GetImagesSize();
		size_t aligment = imageData.GetImagesRequiredAligment();

		auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserving);

		imageData.BindImage(allocationID, beggining);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, size_t addOnReserving)
	{
		auto& imageData = _colorRenderTargets.GetObject(imageID);

		return imageData.AddImageView(addOnReserving);
	}

}