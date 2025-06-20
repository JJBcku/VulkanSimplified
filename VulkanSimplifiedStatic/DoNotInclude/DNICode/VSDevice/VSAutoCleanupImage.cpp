#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupImage.h"

#include "../../DNIHeaders/VSDevice/VSAutoCleanupImageView.h"

namespace VulkanSimplified
{

	VkImage AutoCleanupImage::GetImage() const
	{
		return _image;
	}

	VkImageView AutoCleanupImage::GetImageView(IDObject<AutoCleanupImageView> imageViewID) const
	{
		return _imageViews.GetConstObject(imageViewID).GetImageView();
	}

	uint32_t AutoCleanupImage::GetWidth() const
	{
		return _width;
	}

	uint32_t AutoCleanupImage::GetHeight() const
	{
		return _height;
	}

	uint32_t AutoCleanupImage::GetDepth() const
	{
		return _depth;
	}

	uint32_t AutoCleanupImage::GetMipmapLevels() const
	{
		return _mipmapLevels;
	}

	VkFormat AutoCleanupImage::GetFormat() const
	{
		return _format;
	}

	uint32_t AutoCleanupImage::GetImagesMemoryTypeMask() const
	{
		return _memoryTypeMask;
	}

	MemorySize AutoCleanupImage::GetImagesSize() const
	{
		return _size;
	}

	MemorySize AutoCleanupImage::GetImagesRequiredAligment() const
	{
		return _aligment;
	}

	VkSampleCountFlagBits AutoCleanupImage::GetSampleCount() const
	{
		return _sampleCount;
	}

	std::optional<MemorySuballocationFullID> AutoCleanupImage::GetBoundMemorySuballocation() const
	{
		return _memorySuballocation;
	}

	bool AutoCleanupImage::DeleteImageView(IDObject<AutoCleanupImageView> imageViewID, bool throwOnIDNotFound)
	{
		return _imageViews.RemoveObject(imageViewID, throwOnIDNotFound);
	}

	void AutoCleanupImage::ResetImageViewList(size_t newImageViewListCapacity)
	{
		_imageViews.Reset(newImageViewListCapacity);
	}

	void AutoCleanupImage::BindImage(MemoryAllocationFullID allocationID, size_t bindingBeggining)
	{
		if (_memorySuballocation.has_value())
			throw std::runtime_error("AutoCleanupImage::BindImage Error: Program tried to bind an already bound image!");

		_memorySuballocation.emplace(allocationID, bindingBeggining);
	}

	AutoCleanupImage::AutoCleanupImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipmapLevels, VkFormat format,
		VkSampleCountFlagBits sampleCount, size_t imageViewsInitialCapacity) : _device(device), _image(image), _width(width), _height(height), _depth(depth),
		_mipmapLevels(mipmapLevels), _format(format), _sampleCount(sampleCount), _padding(0), _imageViews(imageViewsInitialCapacity)
	{
		VkMemoryRequirements req{};

		vkGetImageMemoryRequirements(_device, image, &req);

		_memoryTypeMask = req.memoryTypeBits;
		_size = req.size;
		_aligment = req.alignment;
	}

	AutoCleanupImage::~AutoCleanupImage()
	{
		DestroyImage();
	}

	AutoCleanupImage::AutoCleanupImage(AutoCleanupImage&& rhs) noexcept : _device(rhs._device), _image(rhs._image), _width(rhs._width), _height(rhs._height), _depth(rhs._depth),
		_mipmapLevels(rhs._mipmapLevels), _format(rhs._format), _memoryTypeMask(rhs._memoryTypeMask), _size(rhs._size), _aligment(rhs._aligment), _sampleCount(rhs._sampleCount),
		_padding(0), _memorySuballocation(std::move(rhs._memorySuballocation)), _imageViews(std::move(rhs._imageViews))
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._image = VK_NULL_HANDLE;

		rhs._width = 0;
		rhs._height = 0;
		rhs._depth = 0;
		rhs._mipmapLevels = 0;

		rhs._format = VK_FORMAT_MAX_ENUM;
		rhs._memoryTypeMask = 0;
		rhs._size = 0;
		rhs._aligment = 0;

		rhs._sampleCount = VK_SAMPLE_COUNT_1_BIT;
	}

	AutoCleanupImage& AutoCleanupImage::operator=(AutoCleanupImage&& rhs) noexcept
	{
		DestroyImage();

		_device = rhs._device;
		_image = rhs._image;
		
		_width = rhs._width;
		_height = rhs._height;
		_depth = rhs._depth;
		_mipmapLevels = rhs._mipmapLevels;

		_format = rhs._format;
		_memoryTypeMask = rhs._memoryTypeMask;
		_size = rhs._size;
		_aligment = rhs._aligment;

		_sampleCount = rhs._sampleCount;
		_padding = 0;

		_memorySuballocation = std::move(rhs._memorySuballocation);

		_imageViews = std::move(rhs._imageViews);

		rhs._device = VK_NULL_HANDLE;
		rhs._image = VK_NULL_HANDLE;

		rhs._width = 0;
		rhs._height = 0;
		rhs._depth = 0;
		rhs._mipmapLevels = 0;

		rhs._format = VK_FORMAT_MAX_ENUM;
		rhs._memoryTypeMask = 0;
		rhs._size = 0;
		rhs._aligment = 0;

		rhs._sampleCount = VK_SAMPLE_COUNT_1_BIT;

		return *this;
	}

	IDObject<AutoCleanupImageView> AutoCleanupImage::AddImageView(VkComponentMapping componentMapping, VkImageSubresourceRange subresourceRange, VkImageViewType viewType,
		size_t addOnReserving)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = _image;
		createInfo.viewType = viewType;
		createInfo.format = _format;
		createInfo.components = componentMapping;
		createInfo.subresourceRange = subresourceRange;

		VkImageView add = VK_NULL_HANDLE;

		if (vkCreateImageView(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("AutoCleanupImage::AddImageView Error: Program failed to create an image view!");

		return _imageViews.AddObject(AutoCleanupImageView(_device, add), addOnReserving);
	}

	void AutoCleanupImage::DestroyImage()
	{
		_imageViews.Reset(0);

		if (_image != VK_NULL_HANDLE)
		{
			vkDestroyImage(_device, _image, nullptr);

			_device = VK_NULL_HANDLE;
			_image = VK_NULL_HANDLE;
		}
	}

}