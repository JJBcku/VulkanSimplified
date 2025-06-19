#include "VSCommonNIpch.h"
#include "../../DNIHeaders/VSCommon/VSAccessFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	VkAccessFlags TranslataAccessFlags(VulkanSimplified::AccessFlags accessFlags)
	{
		VkAccessFlags ret = 0;

		if (accessFlags == VulkanSimplified::AccessFlagBits::ACCESS_NONE)
			return ret;

		if ((accessFlags & VulkanSimplified::ACCESS_INDIRECT_COMMAND_READ) == VulkanSimplified::ACCESS_INDIRECT_COMMAND_READ)
			ret |= VK_ACCESS_INDIRECT_COMMAND_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_INDEX_READ) == VulkanSimplified::ACCESS_INDEX_READ)
			ret |= VK_ACCESS_INDEX_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_VERTEX_ATTRIBUTE_READ) == VulkanSimplified::ACCESS_VERTEX_ATTRIBUTE_READ)
			ret |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_UNIFORM_READ) == VulkanSimplified::ACCESS_UNIFORM_READ)
			ret |= VK_ACCESS_UNIFORM_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_INPUT_ATTACHMENT_READ) == VulkanSimplified::ACCESS_INPUT_ATTACHMENT_READ)
			ret |= VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_SHADER_READ) == VulkanSimplified::ACCESS_SHADER_READ)
			ret |= VK_ACCESS_SHADER_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_SHADER_WRITE) == VulkanSimplified::ACCESS_SHADER_WRITE)
			ret |= VK_ACCESS_SHADER_WRITE_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_COLOR_ATTACHMENT_READ) == VulkanSimplified::ACCESS_COLOR_ATTACHMENT_READ)
			ret |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_COLOR_ATTACHMENT_WRITE) == VulkanSimplified::ACCESS_COLOR_ATTACHMENT_WRITE)
			ret |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_DEPTH_STENCIL_READ) == VulkanSimplified::ACCESS_DEPTH_STENCIL_READ)
			ret |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_DEPTH_STENCIL_WRITE) == VulkanSimplified::ACCESS_DEPTH_STENCIL_WRITE)
			ret |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_TRANSFER_READ) == VulkanSimplified::ACCESS_TRANSFER_READ)
			ret |= VK_ACCESS_TRANSFER_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_TRANSFER_WRITE) == VulkanSimplified::ACCESS_TRANSFER_WRITE)
			ret |= VK_ACCESS_TRANSFER_WRITE_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_HOST_READ) == VulkanSimplified::ACCESS_HOST_READ)
			ret |= VK_ACCESS_HOST_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_HOST_WRITE) == VulkanSimplified::ACCESS_HOST_WRITE)
			ret |= VK_ACCESS_HOST_WRITE_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_MEMORY_READ) == VulkanSimplified::ACCESS_MEMORY_READ)
			ret |= VK_ACCESS_MEMORY_READ_BIT;

		if ((accessFlags & VulkanSimplified::ACCESS_MEMORY_WRITE) == VulkanSimplified::ACCESS_MEMORY_WRITE)
			ret |= VK_ACCESS_MEMORY_WRITE_BIT;

		return ret;
	}
}