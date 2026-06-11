#pragma once

namespace VulkanSimplified
{
	struct SdlSystemThemeChangeEventData
	{
		uint32_t reserved;
		uint32_t padding;
		uint64_t timestamp;

		SdlSystemThemeChangeEventData();
		~SdlSystemThemeChangeEventData();
	};
}