#include "VSDeviceNIpch.h"
#include "VSImageDataListsInternal.h"

#include "../../Include/VSCommon/VSDataFormatFlags.h"
#include "../../Include/VSCommon/VSImageUsageFlags.h"

#include "../../Include/VSDevice/VSImageDataListsInitialCapacities.h"
#include "../../Include/VSDevice/VSMultitypeImagesID.h"

#include "VSAutoCleanupColorRenderTargetImage.h"
#include "VSAutoCleanup2DTexture.h"
#include "VSAutoCleanupFramebuffer.h"
#include "VSAutoCleanupSampler.h"

#include "VSDeviceCoreInternal.h"
#include "VSMemoryObjectsListInternal.h"
#include "VSRenderPassDataListInternal.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"
#include "../VSCommon/VSImageUsageFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	ImageDataListsInternal::ImageDataListsInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& renderPassData, MemoryObjectsListInternal& memoryList,
		VkDevice device, const VulkanSimplified::ImageDataListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _renderPassData(renderPassData), _memoryList(memoryList),
		_device(device), _colorRenderTargetList(initialCapacities.colorRenderTargetsListInitialCapacity), _2dTexturesList(initialCapacities.twoDTexturesListInitialCapacity),
		_framebufferList(initialCapacities.framebufferListInitialCapacity), _samplerList(initialCapacities.samplerListInitialCapacity)
	{
	}

	ImageDataListsInternal::~ImageDataListsInternal()
	{
	}

	IDObject<AutoCleanupColorRenderTargetImage> ImageDataListsInternal::AddColorRenderTargetImage(uint32_t width, uint32_t height, VulkanSimplified::DataFormatSetIndependentID format,
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
			throw std::runtime_error("ImageDataListsInternal::AddColorRenderTargetImage Error: Program failed to create an image!");

		return _colorRenderTargetList.AddObject(AutoCleanupColorRenderTargetImage(_device, image, width, height, createInfo.format,
			initialImageViewListCapacity), addOnReserving);
	}

	IDObject<AutoCleanup2DTexture> ImageDataListsInternal::Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, VulkanSimplified::DataFormatSetIndependentID format,
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

		createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

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

	VkImage ImageDataListsInternal::Get2DTextureImage(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImage();
	}

	VkImageView ImageDataListsInternal::Get2DTextureImageImageView(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID) const
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

	VulkanSimplified::MemorySize ImageDataListsInternal::GetColorRenderTargetImagesSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImagesSize();
	}

	VulkanSimplified::MemorySize ImageDataListsInternal::GetColorRenderTargetImagesRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _colorRenderTargetList.GetConstObject(imageID).GetImagesRequiredAligment();
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

	VulkanSimplified::MemorySize ImageDataListsInternal::Get2DTextureImagesSize(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImagesSize();
	}

	VulkanSimplified::MemorySize ImageDataListsInternal::Get2DTextureImagesRequiredAligment(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _2dTexturesList.GetConstObject(imageID).GetImagesRequiredAligment();
	}

	void ImageDataListsInternal::BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, VulkanSimplified::MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		auto& imageData = _colorRenderTargetList.GetObject(imageID);

		VkImage image = imageData.GetImage();
		size_t size = imageData.GetImagesSize();
		size_t aligment = imageData.GetImagesRequiredAligment();

		auto beggining = _memoryList.BindImage(allocationID, image, size, aligment, addOnReserving);

		imageData.BindImage(allocationID, beggining);
	}

	void ImageDataListsInternal::Bind2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving)
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
		const std::vector<std::pair<VulkanSimplified::MultitypeImagesID, IDObject<AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
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
			case VulkanSimplified::ImageIDType::COLOR_RENDER_TARGET:
				imageViews.push_back(GetColorRenderTargetImageView(imageID.colorRenderTarget.ID, attachmentData.second));
				break;
			case VulkanSimplified::ImageIDType::UNKNOWN:
			default:
				throw std::runtime_error("ImageDataListsInternal::AddFramebuffer Error: Program was given an erroneous value for a attachments image ID type!");
			}
		}

		createInfo.attachmentCount = static_cast<std::uint32_t>(imageViews.size());
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

}