#include "VSMainIpch.h"
#include "VSMain.h"

#include "../../NoInclude/VSMain/VSMainInternal.h"

#include "VSMainInitData.h"

#include "EventHandler/SdlEventHandler.h"

namespace VulkanSimplified
{
	Main::Main(const MainInitData& initData)
	{
		_internal = std::make_unique<VulkanSimplifiedInternal::MainInternal>(initData);
	}

	Main::~Main()
	{
	}

	SdlEventHandler Main::GetSdlEventHandler()
	{
		return _internal->GetSdlEventHandler();
	}

	const SdlEventHandler Main::GetSdlEventHandler() const
	{
		return _internal->GetSdlEventHandler();
	}

	VulkanVersionData Main::GetAppVersion() const
	{
		return _internal->GetAppVersion();
	}

	VulkanVersionData Main::GetMaxAvailableVulkanVersion() const
	{
		return _internal->GetMaxAvailableVulkanVersion();
	}

	InstanceExtensionPacksList Main::GetAvailableInstanceExtensionPacks() const
	{
		return _internal->GetAvailableInstanceExtensionPacks();
	}

	InstanceLayerPacksList Main::GetAvailableInstanceLayerPacks() const
	{
		return _internal->GetAvailableInstanceLayerPacks();
	}

}
