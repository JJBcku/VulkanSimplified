#pragma once

namespace VulkanSimplified
{
	struct SdlQuitEventData
	{
		uint32_t timestamp;

		SdlQuitEventData();
		~SdlQuitEventData();
	};
}
