#include "VsCommonIpch.h"
#include "VulkanVersionData.h"

namespace VulkanSimplified
{
	VulkanVersionData::VulkanVersionData(uint16_t variant, uint16_t major, uint16_t minor, uint16_t patch)
	{
		if (variant > 7)
			throw std::runtime_error("VulkanVersionData Error: Program was given too big value for variant!");

		if (major > 0x7F)
			throw std::runtime_error("VulkanVersionData Error: Program was given too big value for major version!");

		if (minor > 0x3FF)
			throw std::runtime_error("VulkanVersionData Error: Program was given too big value for minor version!");

		if (patch > 0xFFF)
			throw std::runtime_error("VulkanVersionData Error: Program was given too big value for patch version!");

		_variant = variant;
		_major = major;
		_minor = minor;
		_patch = patch;
	}

	VulkanVersionData::VulkanVersionData(uint32_t vulkanApiVersion)
	{
		_variant = vulkanApiVersion >> 29;
		_major = (vulkanApiVersion >> 22) & 0x7F;
		_minor = (vulkanApiVersion >> 12) & 0x3FF;
		_patch = vulkanApiVersion & 0xFFF;
	}

	uint32_t VulkanVersionData::GetVulkanApiCompatibleVersion() const
	{
		return VK_MAKE_API_VERSION(_variant, _major, _minor, _patch);
	}

	uint16_t VulkanVersionData::GetVulkanVariantVersion() const
	{
		return _variant;
	}

	uint16_t VulkanVersionData::GetVulkanMajorVersion() const
	{
		return _major;
	}

	uint16_t VulkanVersionData::GetVulkanMinorVersion() const
	{
		return _minor;
	}

	uint16_t VulkanVersionData::GetVulkanPatchVersion() const
	{
		return _patch;
	}

	void VulkanVersionData::SetVulkanVariantVersion(uint16_t variant)
	{
		if (variant > 7)
			throw std::runtime_error("VulkanVersionData SetVulkanVariantVersion Error: Program was given too big value for variant version!");

		_variant = variant;
	}

	void VulkanVersionData::SetVulkanMajorVersion(uint16_t major)
	{
		if (major > 0x7F)
			throw std::runtime_error("VulkanVersionData SetVulkanMajorVersion Error: Program was given too big value for major version!");

		_major = major;
	}

	void VulkanVersionData::SetVulkanMinorVersion(uint16_t minor)
	{
		if (minor > 0x3FF)
			throw std::runtime_error("VulkanVersionData SetVulkanMinorVersion Error: Program was given too big value for minor version!");

		_minor = minor;
	}

	void VulkanVersionData::SetVulkanPatchVersion(uint16_t patch)
	{
		if (patch > 0xFFF)
			throw std::runtime_error("VulkanVersionData SetVulkanPatchVersion Error: Program was given too big value for patch version!");

		_patch = patch;
	}
}