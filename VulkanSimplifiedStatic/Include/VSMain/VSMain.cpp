#include "VSMainIpch.h"
#include "VSMain.h"

#include "../../NoInclude/VSMain/VSMainInternal.h"

#include "VSMainInitData.h"

#include "EventHandler/SdlEventHandler.h"

namespace VulkanSimplified
{
	VSMain::VSMain(const VSMainInitData& initData)
	{
		_internal = std::make_unique<VulkanSimplifiedInternal::VSMainInternal>(initData);
	}

	VSMain::~VSMain()
	{
	}

	SdlEventHandler VSMain::GetSdlEventHandler()
	{
		return _internal->GetSdlEventHandler();
	}

	const SdlEventHandler VSMain::GetSdlEventHandler() const
	{
		return _internal->GetSdlEventHandler();
	}
}
