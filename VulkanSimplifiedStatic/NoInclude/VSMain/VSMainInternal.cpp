#include "VSMainNIpch.h"
#include "VSMainInternal.h"

#include "../../Include/VSMain/VSMainInitData.h"

namespace VulkanSimplifiedInternal
{
	VSMainInternal::VSMainInternal(const VulkanSimplified::VSMainInitData& initData) : _eventHandler(initData.eventHandlerData), stump(initData.stump)
	{
	}

	VSMainInternal::~VSMainInternal()
	{
	}

	SdlEventHandlerInternal& VSMainInternal::GetSdlEventHandler()
	{
		return _eventHandler;
	}

	const SdlEventHandlerInternal& VSMainInternal::GetSdlEventHandler() const
	{
		return _eventHandler;
	}
}
