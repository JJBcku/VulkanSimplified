#include "VSDeviceDNIpch.h"
#include "VSImageDataListsInternal.h"

#include "../../../Include/VSDevice/VSImageDataListsInitialCapacities.h"
#include "../../../Include/VSDevice/VSMultitypeImagesID.h"

#include "VSAutoCleanupColorRenderTargetImage.h"
#include "VSAutoCleanupDepthStencilRenderTargetImage.h"
#include "VSAutoCleanupResolveRenderTargetImage.h"

#include "VSAutoCleanup2DTexture.h"

#include "VSAutoCleanupFramebuffer.h"
#include "VSAutoCleanupSampler.h"

#include "VSDeviceCoreInternal.h"
#include "VSMemoryObjectsListInternal.h"
#include "VSRenderPassDataListInternal.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"
#include "../VSCommon/VSImageUsageFlagsInternal.h"
#include "../VSCommon/VSImageSampleFlagsInternal.h"

namespace VulkanSimplified
{
	ImageDataListsInternal::ImageDataListsInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& renderPassData, MemoryObjectsListInternal& memoryList,
		VkDevice device, const ImageDataListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _renderPassData(renderPassData), _memoryList(memoryList),
		_device(device), _colorRenderTargetList(initialCapacities.colorRenderTargetsListInitialCapacity),
		_depthStencilRenderTargetList(initialCapacities.depthStencilRenderTargetsListInitialCapacity),
		_resolveRenderTargetList(initialCapacities.resolveRenderTargetsListInitialCapacity), _2dTexturesList(initialCapacities.twoDTexturesListInitialCapacity),
		_framebufferList(initialCapacities.framebufferListInitialCapacity), _samplerList(initialCapacities.samplerListInitialCapacity)
	{
	}

	ImageDataListsInternal::~ImageDataListsInternal()
	{
	}

	IDObject<AutoCleanupColorRenderTargetImage> ImageDataListsInternal::AddColorRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
		ImageSampleFlagBits imageSamples, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
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
		createInfo.samples = TranslateImageSampleFlagBits(imageSamples);
		createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

		createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingImage.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingImage);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
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
			throw std::runtime_error("ImageDataListsInternal::AddColorRenderTargetImage Error: Program failed to create an image!");

		return _colorRenderTargetList.AddObject(AutoCleanupColorRenderTargetImage(_device, image, width, height, createInfo.format, createInfo.samples,
			initialImageViewListCapacity), addOnReserving);
	}

	IDObject<AutoCleanupDepthStencilRenderTargetImage> ImageDataListsInternal::AddDepthStencilRenderTargetImage(uint32_t width, uint32_t height,
		DataFormatSetIndependentID format, ImageSampleFlagBits imageSamples, const std::vector<size_t>& queuesUsingImage, bool preInitialized,
		size_t initialImageViewListCapacity, size_t addOnReserving)
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
		createInfo.samples = TranslateImageSampleFlagBits(imageSamples);
		createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

		createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingImage.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingImage);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
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
			throw std::runtime_error("ImageDataListsInternal::AddDepthStencilRenderTargetImage Error: Program failed to create an image!");

		return _depthStencilRenderTargetList.AddObject(AutoCleanupDepthStencilRenderTargetImage(_device, image, width, height, createInfo.format, createInfo.samples,
			initialImageViewListCapacity), addOnReserving);
	}

	IDObject<AutoCleanupResolveRenderTargetImage> ImageDataListsInternal::AddResolveRenderTargetImage(uint32_t width, uint32_t height,
		DataFormatSetIndependentID format, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity,
		size_t addOnReserving)
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

		createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingImage.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingImage);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
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
			throw std::runtime_error("ImageDataListsInternal::AddResolveRenderTargetImage Error: Program failed to create an image!");

		return _resolveRenderTargetList.AddObject(AutoCleanupResolveRenderTargetImage(_device, image, width, height, createInfo.format, initialImageViewListCapacity), addOnReserving);
	}

	IDObject<AutoCleanup2DTexture> ImageDataListsInternal::Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, DataFormatSetIndependentID format,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		VkImage image = VK_NULL_HANDLE;
		VkImageCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

		createInfo.imageType = VK_IMAGE_TYPE_2D;
		createInfo.format = TranslateDataFormatToVkFormat(format);

		createInfo.extent.width = width;
		createInfo.extent.height = height;
		createInfo.extent.depth = 1;

		createInfo.mipLevels = mipLevel;
		createInfo.arrayLayers = 1;
		createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

		createInfo.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingImage.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingImage);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
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
			throw std::runtime_error("ImageDataListsInternal::Add2DTextureImage Error: Program failed to create an image!");

		return _2dTexturesList.AddObject(AutoCleanup2DTexture(_device, image, width, height, mipLevel, createInfo.format,
			initialImageViewListCapacity), addOnReserving);
	}

	bool ImageDataListsInternal::RemoveColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		bool ret = _colorRenderTargetList.CheckForID(imageID);

		if (!ret && throwOnIDNotFound)
			throw std::runtime_error("ImageDataListInternal::RemoveSingleSampled2DImage Error: Program tried to delete a non-existent image!");

		if (ret)
		{
			auto& imageData = _colorRenderTargetList.GetObject(imageID);

			auto bindingData = imageData.GetBoundMemorySuballocation();

			ret = _colorRenderTargetList.RemoveObject(imageID, true);

			if (bindingData.has_value())
				_memoryList.RemoveSuballocation(bindingData.value(), true);
		}

		return ret;
	}

	bool ImageDataListsInternal::RemoveDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		bool ret = _depthStencilRenderTargetList.CheckForID(imageID);

		if (!ret && throwOnIDNotFound)
			throw std::runtime_error("ImageDataListInternal::RemoveDepthStencilRenderTargetImage Error: Program tried to delete a non-existent image!");

		if (ret)
		{
			auto& imageData = _depthStencilRenderTargetList.GetObject(imageID);

			auto bindingData = imageData.GetBoundMemorySuballocation();

			ret = _depthStencilRenderTargetList.RemoveObject(imageID, true);

			if (bindingData.has_value())
				_memoryList.RemoveSuballocation(bindingData.value(), true);
		}

		return ret;
	}

	bool ImageDataListsInternal::RemoveResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		bool ret = _resolveRenderTargetList.CheckForID(imageID);

		if (!ret && throwOnIDNotFound)
			throw std::runtime_error("ImageDataListInternal::RemoveResolveRenderTargetImage Error: Program tried to delete a non-existent image!");

		if (ret)
		{
			auto& imageData = _resolveRenderTargetList.GetObject(imageID);

			auto bindingData = imageData.GetBoundMemorySuballocation();

			ret = _resolveRenderTargetList.RemoveObject(imageID, true);

			if (bindingData.has_value())
				_memoryList.RemoveSuballocation(bindingData.value(), true);
		}

		return ret;
	}

	bool ImageDataListsInternal::Remove2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, bool throwOnIDNotFound)
	{
		bool ret = _2dTexturesList.CheckForID(imageID);

		if (!ret && throwOnIDNotFound)
			throw std::runtime_error("ImageDataListInternal::RemoveSingleSampled2DImage Error: Program tried to delete a non-existent image!");

		if (ret)
		{
			auto& imageData = _2dTexturesList.GetObject(imageID);

			auto bindingData = imageData.GetBoundMemorySuballocation();

			ret = _2dTexturesList.RemoveObject(imageID, true);

			if (bindingData.has_value())
				_memoryList.RemoveSuballocation(bindingData.value(), true);
		}

		return ret;
	}

	AutoCleanupColorRenderTargetImage& ImageDataListsInternal::GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID)
	{
		return _colorRenderTargetList.GetObject(imageID);
	}

	const AutoCleanupColorRenderTargetImage& ImageDataListsInternal::GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID);
	}

	AutoCleanupDepthStencilRenderTargetImage& ImageDataListsInternal::GetDepthStencilRenderTargetImageInternal(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID)
	{
		return _depthStencilRenderTargetList.GetObject(imageID);
	}

	const AutoCleanupDepthStencilRenderTargetImage& ImageDataListsInternal::GetDepthStencilRenderTargetImageInternal(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID);
	}

	AutoCleanupResolveRenderTargetImage& ImageDataListsInternal::GetResolveRenderTargetImageInternal(IDObject<AutoCleanupResolveRenderTargetImage> imageID)
	{
		return _resolveRenderTargetList.GetObject(imageID);
	}

	const AutoCleanupResolveRenderTargetImage& ImageDataListsInternal::GetResolveRenderTargetImageInternal(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID);
	}

	AutoCleanup2DTexture& ImageDataListsInternal::Get2DTextureImageInternal(IDObject<AutoCleanup2DTexture> imageID)
	{
		return _2dTexturesList.GetObject(imageID);
	}

	const AutoCleanup2DTexture& ImageDataListsInternal::Get2DTextureImageInternal(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID);
	}

	VkImage ImageDataListsInternal::GetColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImage();
	}

	VkImageView ImageDataListsInternal::GetColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImageView(viewID);
	}

	VkImage ImageDataListsInternal::GetDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetImage();
	}

	VkImageView ImageDataListsInternal::GetDepthStencilRenderTargetImageView(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetImageView(viewID);
	}

	VkImage ImageDataListsInternal::GetResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetImage();
	}

	VkImageView ImageDataListsInternal::GetResolveRenderTargetImageView(IDObject<AutoCleanupResolveRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetImageView(viewID);
	}

	VkImage ImageDataListsInternal::Get2DTextureImage(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImage();
	}

	VkImageView ImageDataListsInternal::Get2DTextureImageView(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImageView(viewID);
	}

	uint32_t ImageDataListsInternal::GetColorRenderTargetImagesWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetWidth();
	}

	uint32_t ImageDataListsInternal::GetColorRenderTargetImagesHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetHeight();
	}

	uint32_t ImageDataListsInternal::GetColorRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImagesMemoryTypeMask();
	}

	MemorySize ImageDataListsInternal::GetColorRenderTargetImagesSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImagesSize();
	}

	MemorySize ImageDataListsInternal::GetColorRenderTargetImagesRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImagesRequiredAligment();
	}

	uint32_t ImageDataListsInternal::GetDepthStencilRenderTargetImagesWidth(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetWidth();
	}

	uint32_t ImageDataListsInternal::GetDepthStencilRenderTargetImagesHeight(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetHeight();
	}

	uint32_t ImageDataListsInternal::GetDepthStencilRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetImagesMemoryTypeMask();
	}

	MemorySize ImageDataListsInternal::GetDepthStencilRenderTargetImagesSize(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetImagesSize();
	}

	MemorySize ImageDataListsInternal::GetDepthStencilRenderTargetImagesRequiredAligment(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetImagesRequiredAligment();
	}

	VkSampleCountFlagBits ImageDataListsInternal::GetDepthStencilRenderTargetSampleCount(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _depthStencilRenderTargetList.GetConstObject(imageID).GetSampleCount();
	}

	uint32_t ImageDataListsInternal::GetResolveRenderTargetImagesWidth(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetWidth();
	}

	uint32_t ImageDataListsInternal::GetResolveRenderTargetImagesHeight(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetHeight();
	}

	uint32_t ImageDataListsInternal::GetResolveRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetImagesMemoryTypeMask();
	}

	MemorySize ImageDataListsInternal::GetResolveRenderTargetImagesSize(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetImagesSize();
	}

	MemorySize ImageDataListsInternal::GetResolveRenderTargetImagesRequiredAligment(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _resolveRenderTargetList.GetConstObject(imageID).GetImagesRequiredAligment();
	}

	uint32_t ImageDataListsInternal::Get2DTextureImagesWidth(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetWidth();
	}

	uint32_t ImageDataListsInternal::Get2DTextureImagesHeight(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetHeight();
	}

	uint32_t ImageDataListsInternal::Get2DTextureImagesMemoryTypeMask(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImagesMemoryTypeMask();
	}

	MemorySize ImageDataListsInternal::Get2DTextureImagesSize(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImagesSize();
	}

	MemorySize ImageDataListsInternal::Get2DTextureImagesRequiredAligment(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImagesRequiredAligment();
	}

	void ImageDataListsInternal::BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		auto& imageData = _colorRenderTargetList.GetObject(imageID);

		VkImage image = imageData.GetImage();
		size_t size = imageData.GetImagesSize();
		size_t aligment = imageData.GetImagesRequiredAligment();

		auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserving);

		imageData.BindImage(allocationID, beggining);
	}

	void ImageDataListsInternal::BindDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		auto& imageData = _depthStencilRenderTargetList.GetObject(imageID);

		VkImage image = imageData.GetImage();
		size_t size = imageData.GetImagesSize();
		size_t aligment = imageData.GetImagesRequiredAligment();

		auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserving);

		imageData.BindImage(allocationID, beggining);
	}

	void ImageDataListsInternal::BindResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		auto& imageData = _resolveRenderTargetList.GetObject(imageID);

		VkImage image = imageData.GetImage();
		size_t size = imageData.GetImagesSize();
		size_t aligment = imageData.GetImagesRequiredAligment();

		auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserving);

		imageData.BindImage(allocationID, beggining);
	}

	void ImageDataListsInternal::Bind2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& imageData = _2dTexturesList.GetObject(imageID);

		VkImage image = imageData.GetImage();
		size_t size = imageData.GetImagesSize();
		size_t aligment = imageData.GetImagesRequiredAligment();

		auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserving);

		imageData.BindImage(allocationID, beggining);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, size_t addOnReserving)
	{
		auto& imageData = _colorRenderTargetList.GetObject(imageID);

		return imageData.AddImageView(addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::AddDepthStencilRenderTargetImageView(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, size_t addOnReserving)
	{
		auto& imageData = _depthStencilRenderTargetList.GetObject(imageID);

		return imageData.AddImageView(addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::AddResolveRenderTargetImageView(IDObject<AutoCleanupResolveRenderTargetImage> imageID, size_t addOnReserving)
	{
		auto& imageData = _resolveRenderTargetList.GetObject(imageID);

		return imageData.AddImageView(addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::Add2DTextureImageFullView(IDObject<AutoCleanup2DTexture> imageID, size_t addOnReserving)
	{
		auto& imageData = _2dTexturesList.GetObject(imageID);

		return imageData.AddFullImageView(addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::Add2DTextureImageSingleMipmapView(IDObject<AutoCleanup2DTexture> imageID, uint32_t mipmap, size_t addOnReserving)
	{
		auto& imageData = _2dTexturesList.GetObject(imageID);

		return imageData.AddSingleMipmapImageView(mipmap, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::Add2DTextureImageRemainingMipmapsView(IDObject<AutoCleanup2DTexture> imageID, uint32_t startingMipmap, size_t addOnReserving)
	{
		auto& imageData = _2dTexturesList.GetObject(imageID);

		return imageData.AddRemainingMipmapsImageView(startingMipmap, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataListsInternal::Add2DTextureImageSelectedMipmapsView(IDObject<AutoCleanup2DTexture> imageID, uint32_t startingMipmap, uint32_t mipmapCount,
		size_t addOnReserving)
	{
		auto& imageData = _2dTexturesList.GetObject(imageID);

		return imageData.AddSelectedMipmapsImageView(startingMipmap, mipmapCount, addOnReserving);
	}

	IDObject<AutoCleanupFramebuffer> ImageDataListsInternal::AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
		const std::vector<std::pair<RenderTargetImagesID, IDObject<AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
		uint32_t layers, size_t addOnReserving)
	{
		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.renderPass = _renderPassData.GetRenderPass(renderPass);

		std::vector<VkImageView> imageViews;
		imageViews.reserve(attachmentsList.size());

		for (auto& attachmentData : attachmentsList)
		{
			auto& imageID = attachmentData.first;

			switch (imageID.type)
			{
			case ImageIDType::COLOR_RENDER_TARGET:
				imageViews.push_back(GetColorRenderTargetImageView(imageID.colorRenderTarget.ID, attachmentData.second));
				break;
			case ImageIDType::DEPTH_STENCIL_RENDER_TARGET:
				imageViews.push_back(GetDepthStencilRenderTargetImageView(imageID.depthStencilRenderTarget.ID, attachmentData.second));
				break;
			case ImageIDType::RESOLVE_RENDER_TARGET:
				imageViews.push_back(GetResolveRenderTargetImageView(imageID.resolveRenderTarget.ID, attachmentData.second));
				break;
			case ImageIDType::UNKNOWN:
			default:
				throw std::runtime_error("ImageDataListsInternal::AddFramebuffer Error: Program was given an erroneous value for a attachments image ID type!");
			}
		}

		createInfo.attachmentCount = static_cast<uint32_t>(imageViews.size());
		createInfo.pAttachments = imageViews.data();
		createInfo.width = width;
		createInfo.height = height;
		createInfo.layers = layers;

		VkFramebuffer add = VK_NULL_HANDLE;

		if (vkCreateFramebuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("ImageDataListsInternal::AddFramebuffer Error: Program failed to create a framebuffer!");

		return _framebufferList.AddObject(AutoCleanupFramebuffer(_device, add), addOnReserving);
	}

	IDObject<AutoCleanupSampler> ImageDataListsInternal::AddSampler(bool magFilterLinear, bool minFilterLinear, bool mipmapLinear,
		bool addressXMirrored, bool addressYMirrored, bool addressZMirrored, float mipmapBias, float maxAnisotropy, float minLod, const std::optional<float>& maxLod, size_t addOnReserving)
	{
		VkSamplerCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;

		if (magFilterLinear)
			createInfo.magFilter = VK_FILTER_LINEAR;
		else
			createInfo.magFilter = VK_FILTER_NEAREST;

		if (minFilterLinear)
			createInfo.minFilter = VK_FILTER_LINEAR;
		else
			createInfo.minFilter = VK_FILTER_NEAREST;

		if (mipmapLinear)
			createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		else
			createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;

		if (addressXMirrored)
			createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		else
			createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;

		if (addressYMirrored)
			createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		else
			createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;

		if (addressZMirrored)
			createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		else
			createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

		createInfo.mipLodBias = mipmapBias;

		if (maxAnisotropy == 0.0f)
		{
			createInfo.anisotropyEnable = VK_FALSE;
		}
		else
		{
			createInfo.anisotropyEnable = VK_TRUE;
			createInfo.maxAnisotropy = maxAnisotropy;
		}

		createInfo.minLod = minLod;

		if (maxLod.has_value())
			createInfo.maxLod = maxLod.value();
		else
			createInfo.maxLod = VK_LOD_CLAMP_NONE;

		VkSampler add = VK_NULL_HANDLE;

		if (vkCreateSampler(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("ImageDataListsInternal::AddSampler Error: Program failed to create a sampler!");

		return _samplerList.AddObject(AutoCleanupSampler(_device, add), addOnReserving);
	}

	bool ImageDataListsInternal::RemoveFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound)
	{
		return _framebufferList.RemoveObject(framebufferID, throwOnIDNotFound);
	}

	bool ImageDataListsInternal::RemoveSampler(IDObject<AutoCleanupSampler> samplerID, bool throwOnIDNotFound)
	{
		return _samplerList.RemoveObject(samplerID, throwOnIDNotFound);
	}

	VkFramebuffer ImageDataListsInternal::GetFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID) const
	{
		return _framebufferList.GetConstObject(framebufferID).GetFramebuffer();
	}

	VkSampler ImageDataListsInternal::GetSampler(IDObject<AutoCleanupSampler> samplerID) const
	{
		return _samplerList.GetConstObject(samplerID).GetSampler();
	}

	std::vector<VkSampler> ImageDataListsInternal::GetSamplerList(std::vector<IDObject<AutoCleanupSampler>> samplerIDs) const
	{
		std::vector<VkSampler> ret;
		ret.reserve(samplerIDs.size());

		for (size_t i = 0; i < samplerIDs.size(); ++i)
		{
			ret.push_back(GetSampler(samplerIDs[i]));
		}

		return ret;
	}

}