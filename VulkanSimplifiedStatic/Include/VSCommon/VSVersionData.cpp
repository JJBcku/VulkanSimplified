#include "VSCommonIpch.h"
#include "VSVersionData.h"

namespace VulkanSimplified
{
	VersionData::VersionData(uint16_t variant, uint16_t major, uint16_t minor, uint16_t patch)
	{
		if (variant > 7)
			throw std::runtime_error("VersionData Error: Program was given too big value for variant!");

		if (major > 0x7F)
			throw std::runtime_error("VersionData Error: Program was given too big value for major version!");

		if (minor > 0x3FF)
			throw std::runtime_error("VersionData Error: Program was given too big value for minor version!");

		if (patch > 0xFFF)
			throw std::runtime_error("VersionData Error: Program was given too big value for patch version!");

		_variant = variant;
		_major = major;
		_minor = minor;
		_patch = patch;
	}

	VersionData::VersionData(uint32_t vulkanApiVersion)
	{
		_variant = vulkanApiVersion >> 29;
		_major = (vulkanApiVersion >> 22) & 0x7F;
		_minor = (vulkanApiVersion >> 12) & 0x3FF;
		_patch = vulkanApiVersion & 0xFFF;
	}

	uint32_t VersionData::GetVulkanApiCompatibleVersion() const
	{
		return VK_MAKE_API_VERSION(_variant, _major, _minor, _patch);
	}

	uint16_t VersionData::GetVulkanVariantVersion() const
	{
		return _variant;
	}

	uint16_t VersionData::GetVulkanMajorVersion() const
	{
		return _major;
	}

	uint16_t VersionData::GetVulkanMinorVersion() const
	{
		return _minor;
	}

	uint16_t VersionData::GetVulkanPatchVersion() const
	{
		return _patch;
	}

	void VersionData::SetVulkanVariantVersion(uint16_t variant)
	{
		if (variant > 7)
			throw std::runtime_error("VersionData SetVulkanVariantVersion Error: Program was given too big value for variant version!");

		_variant = variant;
	}

	void VersionData::SetVulkanMajorVersion(uint16_t major)
	{
		if (major > 0x7F)
			throw std::runtime_error("VersionData SetVulkanMajorVersion Error: Program was given too big value for major version!");

		_major = major;
	}

	void VersionData::SetVulkanMinorVersion(uint16_t minor)
	{
		if (minor > 0x3FF)
			throw std::runtime_error("VersionData SetVulkanMinorVersion Error: Program was given too big value for minor version!");

		_minor = minor;
	}

	void VersionData::SetVulkanPatchVersion(uint16_t patch)
	{
		if (patch > 0xFFF)
			throw std::runtime_error("VersionData SetVulkanPatchVersion Error: Program was given too big value for patch version!");

		_patch = patch;
	}
}