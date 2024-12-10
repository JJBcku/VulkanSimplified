#pragma once

namespace VulkanSimplified
{
	class VulkanVersionData
	{
	public:
		VulkanVersionData(uint16_t variant = 0, uint16_t major = 0, uint16_t minor = 0, uint16_t patch = 0);
		VulkanVersionData(uint32_t vulkanApiVersion);

		uint32_t GetVulkanApiCompatibleVersion() const;

		uint16_t GetVulkanVariantVersion() const;
		uint16_t GetVulkanMajorVersion() const;
		uint16_t GetVulkanMinorVersion() const;
		uint16_t GetVulkanPatchVersion() const;

		void SetVulkanVariantVersion(uint16_t variant);
		void SetVulkanMajorVersion(uint16_t major);
		void SetVulkanMinorVersion(uint16_t minor);
		void SetVulkanPatchVersion(uint16_t patch);

	private:
		uint16_t _variant;
		uint16_t _major;
		uint16_t _minor;
		uint16_t _patch;
	};
}