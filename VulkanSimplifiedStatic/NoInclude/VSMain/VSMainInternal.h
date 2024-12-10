#pragma once

#include "EventHandler/SdlEventHandlerInternal.h"

namespace VulkanSimplified
{
	struct VSMainInitData;
}

namespace VulkanSimplifiedInternal
{
	class VSMainInternal
	{
	public:
		VSMainInternal(const VulkanSimplified::VSMainInitData& initData);
		~VSMainInternal();

		SdlEventHandlerInternal& GetSdlEventHandler();

		const SdlEventHandlerInternal& GetSdlEventHandler() const;

	private:
		SdlEventHandlerInternal _eventHandler;

		uint64_t stump;
	};
}