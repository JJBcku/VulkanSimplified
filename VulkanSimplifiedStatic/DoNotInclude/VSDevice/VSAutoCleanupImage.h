#pragma once

#include "CustomLists/UnsortedIDVector.h"

#include "../../Include/VSCommon/VSMemorySizeDef.h"

#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"

#include "../../Include/VSCommon/VSMemoryAllocationFullID.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupImageView;

	class AutoCleanupImage
	{
	public:
		VkImage GetImage() const;
		VkImageView GetImageView(IDObject<AutoCleanupImageView> imageViewID) const;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		uint32_t GetDepth() const;
		uint32_t GetMipmapLevels() const;

		VkFormat GetFormat() const;
		VkImageLayout GetLayout() const;

		uint32_t GetImagesMemoryTypeMask() const;
		VulkanSimplified::MemorySize GetImagesSize() const;
		VulkanSimplified::MemorySize GetImagesRequiredAligment() const;

		std::optional<VulkanSimplified::MemorySuballocationFullID> GetBoundMemorySuballocation() const;

		bool DeleteImageView(IDObject<AutoCleanupImageView> imageViewID, bool throwOnIDNotFound);
		void ResetImageViewList(size_t newImageViewListCapacity);

		void BindImage(VulkanSimplified::MemoryAllocationFullID allocationID, size_t bindingBeggining);

		void SetLayout(VkImageLayout newLayout);

	protected:
		AutoCleanupImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipmapLevels, VkFormat format, VkImageLayout layout,
			size_t imageViewsInitialCapacity);
		~AutoCleanupImage();

		AutoCleanupImage(const AutoCleanupImage& rhs) noexcept = delete;
		AutoCleanupImage(AutoCleanupImage&& rhs) noexcept;

		AutoCleanupImage& operator=(const AutoCleanupImage& rhs) noexcept = delete;
		AutoCleanupImage& operator=(AutoCleanupImage&& rhs) noexcept;

		IDObject<AutoCleanupImageView> AddImageView(VkComponentMapping componentMapping, VkImageSubresourceRange subresourceRange, VkImageViewType viewType, size_t addOnReserving);

	private:
		VkDevice _device;
		VkImage _image;

		uint32_t _width;
		uint32_t _height;
		uint32_t _depth;
		uint32_t _mipmapLevels;

		VkFormat _format;
		VkImageLayout _layout;
		uint32_t _memoryTypeMask;
		VulkanSimplified::MemorySize _size;
		VulkanSimplified::MemorySize _aligment;

		std::optional<VulkanSimplified::MemorySuballocationFullID> _memorySuballocation;

		UnsortedIDVector<AutoCleanupImageView> _imageViews;

		void DestroyImage();
	};
}