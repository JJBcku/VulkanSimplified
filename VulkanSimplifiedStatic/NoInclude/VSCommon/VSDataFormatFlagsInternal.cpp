#include "VSCommonNIpch.h"
#include "VSDataFormatFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	VkFormat TranslateDataFormatFirstSetToVKFormat(VulkanSimplified::DataFormatFirstFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_ASTC_12X12_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_12x12_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_12X12_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_12x12_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_12X10_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_12x10_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_12X10_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_12x10_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X8_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_10x8_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X8_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_10x8_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X6_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_10x6_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X6_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_10x6_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X5_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_10x5_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X5_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_10x5_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X10_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_10x10_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_10X10_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_10x10_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_USCALED_PACK32:
			ret = VK_FORMAT_A8B8G8R8_USCALED_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_UNORM_PACK32:
			ret = VK_FORMAT_A8B8G8R8_UNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_UINT_PACK32:
			ret = VK_FORMAT_A8B8G8R8_UINT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_SSCALED_PACK32:
			ret = VK_FORMAT_A8B8G8R8_SSCALED_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_SRGB_PACK32:
			ret = VK_FORMAT_A8B8G8R8_SRGB_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_SNORM_PACK32:
			ret = VK_FORMAT_A8B8G8R8_SNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ABGR8_SINT_PACK32:
			ret = VK_FORMAT_A8B8G8R8_SINT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_RGB10_USCALED_PACK32:
			ret = VK_FORMAT_A2R10G10B10_USCALED_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_RGB10_UNORM_PACK32:
			ret = VK_FORMAT_A2R10G10B10_UNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_RGB10_UINT_PACK32:
			ret = VK_FORMAT_A2R10G10B10_UINT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_RGB10_SSCALED_PACK32:
			ret = VK_FORMAT_A2R10G10B10_SSCALED_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_RGB10_SNORM_PACK32:
			ret = VK_FORMAT_A2R10G10B10_SNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_RGB10_SINT_PACK32:
			ret = VK_FORMAT_A2R10G10B10_SINT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_BGR10_USCALED_PACK32:
			ret = VK_FORMAT_A2B10G10R10_USCALED_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_BGR10_UNORM_PACK32:
			ret = VK_FORMAT_A2B10G10R10_UNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_BGR10_UINT_PACK32:
			ret = VK_FORMAT_A2B10G10R10_UINT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_BGR10_SSCALED_PACK32:
			ret = VK_FORMAT_A2B10G10R10_SSCALED_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_BGR10_SNORM_PACK32:
			ret = VK_FORMAT_A2B10G10R10_SNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A2_BGR10_SINT_PACK32:
			ret = VK_FORMAT_A2B10G10R10_SINT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_A1_RGB5_UNORM_PACK16:
			ret = VK_FORMAT_A1R5G5B5_UNORM_PACK16;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatSecondSetToVKFormat(VulkanSimplified::DataFormatSecondFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_BGRA8_SSCALED:
			ret = VK_FORMAT_B8G8R8A8_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA8_SRGB:
			ret = VK_FORMAT_B8G8R8A8_SRGB;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA8_SNORM:
			ret = VK_FORMAT_B8G8R8A8_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA8_SINT:
			ret = VK_FORMAT_B8G8R8A8_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_BGR8_UNORM:
			ret = VK_FORMAT_B8G8R8_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_BGR8_UINT:
			ret = VK_FORMAT_B8G8R8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_BGR8_SRGB:
			ret = VK_FORMAT_B8G8R8_SRGB;
			break;
		case VulkanSimplified::DATA_FORMAT_BGR8_SNORM:
			ret = VK_FORMAT_B8G8R8_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_BGR8_SINT:
			ret = VK_FORMAT_B8G8R8_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_B5_G6_R5_UNORM_PACK16:
			ret = VK_FORMAT_B5G6R5_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_BGR5_A1_UNORM_PACK16:
			ret = VK_FORMAT_B5G5R5A1_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA4_UNORM_PACK16:
			ret = VK_FORMAT_B4G4R4A4_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRG16_422_UNORM:
			ret = VK_FORMAT_B16G16R16G16_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_B12X4_G12X4_R12X4_G12X4_422_UNORM_4PACK16:
			ret = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_B10X6_G10X6_R10X6_G10X6_422_UNORM_4PACK16:
			ret = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_B10_GR11_UFLOAT_PACK32:
			ret = VK_FORMAT_B10G11R11_UFLOAT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_8X8_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_8x8_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_8X8_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_8x8_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_8X6_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_8x6_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_8X6_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_8x6_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_8X5_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_8x5_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_8X5_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_8x5_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_6X6_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_6x6_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_6X6_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_6x6_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_6X5_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_6x5_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_6X5_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_6x5_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_5X5_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_5x5_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_5X5_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_5x5_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_5X4_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_5x4_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_5X4_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_5x4_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_4X4_UNORM_PACK32:
			ret = VK_FORMAT_ASTC_4x4_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ASTC_4X4_SRGB_PACK32:
			ret = VK_FORMAT_ASTC_4x4_SRGB_BLOCK;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatThirdSetToVKFormat(VulkanSimplified::DataFormatThirdFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_ETC2_RGB8_UNORM_BLOCK:
			ret = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ETC2_RGB8_SRGB_BLOCK:
			ret = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_EAC_RG11_UNORM_BLOCK:
			ret = VK_FORMAT_EAC_R11G11_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_EAC_RG11_SNORM_BLOCK:
			ret = VK_FORMAT_EAC_R11G11_SNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_EAC_R11_UNORM_BLOCK:
			ret = VK_FORMAT_EAC_R11_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_EAC_R11_SNORM_BLOCK:
			ret = VK_FORMAT_EAC_R11_SNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_E5_BGR9_UFLOAT_PACK32:
			ret = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_D32_SFLOAT_S8_UINT:
			ret = VK_FORMAT_D32_SFLOAT_S8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_D32_SFLOAT:
			ret = VK_FORMAT_D32_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_D24_UNORM_S8_UINT:
			ret = VK_FORMAT_D24_UNORM_S8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_D16_UNORM_S8_UINT:
			ret = VK_FORMAT_D16_UNORM_S8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_D16_UNORM:
			ret = VK_FORMAT_D16_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_BC7_UNORM_BLOCK:
			ret = VK_FORMAT_BC7_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC7_SRGB_BLOCK:
			ret = VK_FORMAT_BC7_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC6H_UFLOAT_BLOCK:
			ret = VK_FORMAT_BC6H_UFLOAT_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC6H_SFLOAT_BLOCK:
			ret = VK_FORMAT_BC6H_SFLOAT_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC5_UNORM_BLOCK:
			ret = VK_FORMAT_BC5_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC5_SNORM_BLOCK:
			ret = VK_FORMAT_BC5_SNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC4_UNORM_BLOCK:
			ret = VK_FORMAT_BC4_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC4_SNORM_BLOCK:
			ret = VK_FORMAT_BC4_SNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC3_UNORM_BLOCK:
			ret = VK_FORMAT_BC3_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC3_SRGB_BLOCK:
			ret = VK_FORMAT_BC3_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC2_UNORM_BLOCK:
			ret = VK_FORMAT_BC2_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC2_SRGB_BLOCK:
			ret = VK_FORMAT_BC2_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC1_RGBA_UNORM_BLOCK:
			ret = VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC1_RGBA_SRGB_BLOCK:
			ret = VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC1_RGB_UNORM_BLOCK:
			ret = VK_FORMAT_BC1_RGB_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BC1_RGB_SRGB_BLOCK:
			ret = VK_FORMAT_BC1_RGB_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRG8_422_UNORM:
			ret = VK_FORMAT_B8G8R8G8_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA8_USCALED:
			ret = VK_FORMAT_B8G8R8A8_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA8_UNORM:
			ret = VK_FORMAT_B8G8R8A8_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_BGRA8_UINT:
			ret = VK_FORMAT_B8G8R8A8_UINT;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatFourthSetToVKFormat(VulkanSimplified::DataFormatFourthFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_R12X4_G12X4_UNORM_2PACK16:
			ret = VK_FORMAT_R12X4G12X4_UNORM_2PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_R12X4_UNORM_PACK16:
			ret = VK_FORMAT_R12X4_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_R10X6_G10X6_B10X6_A10X6_UNORM_4PACK16:
			ret = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_R10X6_G10X6_UNORM_2PACK16:
			ret = VK_FORMAT_R10X6G10X6_UNORM_2PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_R10X6_UNORM_PACK16:
			ret = VK_FORMAT_R10X6_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_GBGR8_422_UNORM:
			ret = VK_FORMAT_G8B8G8R8_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G8_BR8_2PLANE_422_UNORM:
			ret = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G8_BR8_2PLANE_420_UNORM:
			ret = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G8_B8_R8_3PLANE_444_UNORM:
			ret = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G8_B8_R8_3PLANE_422_UNORM:
			ret = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G8_B8_R8_3PLANE_420_UNORM:
			ret = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_GBGR16_422_UNORM:
			ret = VK_FORMAT_G16B16G16R16_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G16_BR16_2PLANE_422_UNORM:
			ret = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G16_BR16_2PLANE_420_UNORM:
			ret = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G16_B16_R16_3PLANE_422_UNORM:
			ret = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G16_B16_R16_3PLANE_420_UNORM:
			ret = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_G12X4_B12X4_G12X4_R12X4_422_UNORM_4PACK16:
			ret = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G12X4_BR12X4_2PLANE_422_UNORM_3PACK16:
			ret = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G12X4_BR12X4_2PLANE_420_UNORM_3PACK16:
			ret = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16:
			ret = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16:
			ret = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16:
			ret = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G10X6_B10X6_G10X6_R10X6_422_UNORM_4PACK16:
			ret = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G10X6_BR10X6_2PLANE_422_UNORM_3PACK16:
			ret = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G10X6_BR10X6_2PLANE_420_UNORM_3PACK16:
			ret = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16:
			ret = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16:
			ret = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16:
			ret = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_ETC2_RGBA8_UNORM_BLOCK:
			ret = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ETC2_RGBA8_SRGB_BLOCK:
			ret = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ETC2_RGB8_A1_UNORM_BLOCK:
			ret = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK;
			break;
		case VulkanSimplified::DATA_FORMAT_ETC2_RGB8_A1_SRGB_BLOCK:
			ret = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatFifthSetToVKFormat(VulkanSimplified::DataFormatFifthFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_RG32_SINT:
			ret = VK_FORMAT_R32G32_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG32_SFLOAT:
			ret = VK_FORMAT_R32G32_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_R32_UINT:
			ret = VK_FORMAT_R32_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R32_SINT:
			ret = VK_FORMAT_R32_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R32_SFLOAT:
			ret = VK_FORMAT_R32_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_USCALED:
			ret = VK_FORMAT_R16G16B16A16_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_UNORM:
			ret = VK_FORMAT_R16G16B16A16_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_UINT:
			ret = VK_FORMAT_R16G16B16A16_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_SSCALED:
			ret = VK_FORMAT_R16G16B16A16_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_SNORM:
			ret = VK_FORMAT_R16G16B16A16_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_SINT:
			ret = VK_FORMAT_R16G16B16A16_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA16_SFLOAT:
			ret = VK_FORMAT_R16G16B16A16_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB16_UNORM:
			ret = VK_FORMAT_R16G16B16_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB16_UINT:
			ret = VK_FORMAT_R16G16B16_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB16_SNORM:
			ret = VK_FORMAT_R16G16B16_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB16_SINT:
			ret = VK_FORMAT_R16G16B16_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB16_SFLOAT:
			ret = VK_FORMAT_R16G16B16_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_USCALED:
			ret = VK_FORMAT_R16G16_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_UNORM:
			ret = VK_FORMAT_R16G16_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_UINT:
			ret = VK_FORMAT_R16G16_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_SSCALED:
			ret = VK_FORMAT_R16G16_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_SNORM:
			ret = VK_FORMAT_R16G16_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_SINT:
			ret = VK_FORMAT_R16G16_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG16_SFLOAT:
			ret = VK_FORMAT_R16G16_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_USCALED:
			ret = VK_FORMAT_R16_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_UNORM:
			ret = VK_FORMAT_R16_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_UINT:
			ret = VK_FORMAT_R16_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_SSCALED:
			ret = VK_FORMAT_R16_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_SNORM:
			ret = VK_FORMAT_R16_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_SINT:
			ret = VK_FORMAT_R16_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R16_SFLOAT:
			ret = VK_FORMAT_R16_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_R12X4_G12X4_B12X4_A12X4_UNORM_4PACK16:
			ret = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatSixthSetToVKFormat(VulkanSimplified::DataFormatSixthFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_RG8_USCALED:
			ret = VK_FORMAT_R8G8_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RG8_UNORM:
			ret = VK_FORMAT_R8G8_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RG8_UINT:
			ret = VK_FORMAT_R8G8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG8_SSCALED:
			ret = VK_FORMAT_R8G8_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RG8_SRGB:
			ret = VK_FORMAT_R8G8_SRGB;
			break;
		case VulkanSimplified::DATA_FORMAT_RG8_SNORM:
			ret = VK_FORMAT_R8G8_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RG8_SINT:
			ret = VK_FORMAT_R8G8_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_USCALED:
			ret = VK_FORMAT_R8_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_UNORM:
			ret = VK_FORMAT_R8_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_UINT:
			ret = VK_FORMAT_R8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_SSCALED:
			ret = VK_FORMAT_R8_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_SRGB:
			ret = VK_FORMAT_R8_SRGB;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_SNORM:
			ret = VK_FORMAT_R8_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_R8_SINT:
			ret = VK_FORMAT_R8_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA64_UINT:
			ret = VK_FORMAT_R64G64B64A64_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA64_SINT:
			ret = VK_FORMAT_R64G64B64A64_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG64_UINT:
			ret = VK_FORMAT_R64G64_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG64_SINT:
			ret = VK_FORMAT_R64G64_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R64_UINT:
			ret = VK_FORMAT_R64_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R64_SINT:
			ret = VK_FORMAT_R64_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_R64_SFLOAT:
			ret = VK_FORMAT_R64_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_R5_G6_B5_UNORM_PACK16:
			ret = VK_FORMAT_R5G6B5_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB5_A1_UNORM_PACK16:
			ret = VK_FORMAT_R5G5B5A1_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA4_UNORM_PACK16:
			ret = VK_FORMAT_R4G4B4A4_UNORM_PACK16;
			break;
		case VulkanSimplified::DATA_FORMAT_RG4_UNORM_PACK8:
			ret = VK_FORMAT_R4G4_UNORM_PACK8;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA32_UINT:
			ret = VK_FORMAT_R32G32B32A32_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA32_SINT:
			ret = VK_FORMAT_R32G32B32A32_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA32_SFLOAT:
			ret = VK_FORMAT_R32G32B32A32_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB32_UINT:
			ret = VK_FORMAT_R32G32B32_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB32_SINT:
			ret = VK_FORMAT_R32G32B32_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB32_SFLOAT:
			ret = VK_FORMAT_R32G32B32_SFLOAT;
			break;
		case VulkanSimplified::DATA_FORMAT_RG32_UINT:
			ret = VK_FORMAT_R32G32_UINT;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatSeventhSetToVKFormat(VulkanSimplified::DataFormatSeventhFlagSetBits format)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (format)
		{
		case VulkanSimplified::DATA_FORMAT_X8D24_UNORM_PACK32:
			ret = VK_FORMAT_X8_D24_UNORM_PACK32;
			break;
		case VulkanSimplified::DATA_FORMAT_S8_UINT:
			ret = VK_FORMAT_S8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_USCALED:
			ret = VK_FORMAT_R8G8B8A8_USCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_UNORM:
			ret = VK_FORMAT_R8G8B8A8_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_UINT:
			ret = VK_FORMAT_R8G8B8A8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_SSCALED:
			ret = VK_FORMAT_R8G8B8A8_SSCALED;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_SRGB:
			ret = VK_FORMAT_R8G8B8A8_SRGB;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_SNORM:
			ret = VK_FORMAT_R8G8B8A8_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGBA8_SINT:
			ret = VK_FORMAT_R8G8B8A8_SINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB8_UNORM:
			ret = VK_FORMAT_R8G8B8_UNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB8_UINT:
			ret = VK_FORMAT_R8G8B8_UINT;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB8_SRGB:
			ret = VK_FORMAT_R8G8B8_SRGB;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB8_SNORM:
			ret = VK_FORMAT_R8G8B8_SNORM;
			break;
		case VulkanSimplified::DATA_FORMAT_RGB8_SINT:
			ret = VK_FORMAT_R8G8B8_SINT;
			break;
		default:
			break;
		}

		return ret;
	}

	VkFormat TranslateDataFormatToVkFormat(VulkanSimplified::DataFormatSetIndependentID formatID)
	{
		VkFormat ret = VK_FORMAT_UNDEFINED;

		switch (formatID.dataSet)
		{
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_UNKNOWN:
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_ONE:
			ret = TranslateDataFormatFirstSetToVKFormat(static_cast<VulkanSimplified::DataFormatFirstFlagSetBits>(formatID.dataFormat));
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_TWO:
			ret = TranslateDataFormatSecondSetToVKFormat(static_cast<VulkanSimplified::DataFormatSecondFlagSetBits>(formatID.dataFormat));
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_THREE:
			ret = TranslateDataFormatThirdSetToVKFormat(static_cast<VulkanSimplified::DataFormatThirdFlagSetBits>(formatID.dataFormat));
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_FOUR:
			ret = TranslateDataFormatFourthSetToVKFormat(static_cast<VulkanSimplified::DataFormatFourthFlagSetBits>(formatID.dataFormat));
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_FIVE:
			ret = TranslateDataFormatFifthSetToVKFormat(static_cast<VulkanSimplified::DataFormatFifthFlagSetBits>(formatID.dataFormat));
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_SIX:
			ret = TranslateDataFormatSixthSetToVKFormat(static_cast<VulkanSimplified::DataFormatSixthFlagSetBits>(formatID.dataFormat));
			break;
		case VulkanSimplified::DataFormatSetEnum::DATA_SET_SEVEN:
			ret = TranslateDataFormatSeventhSetToVKFormat(static_cast<VulkanSimplified::DataFormatSeventhFlagSetBits>(formatID.dataFormat));
			break;
		default:
			break;
		}

		return ret;
	}
}