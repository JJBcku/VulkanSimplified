#include "VSMainIpch.h"
#include "VSMain.h"

#include "../../DoNotInclude/VSMain/VSMainInternal.h"

#include "VSMainInitData.h"

#include "EventHandler/SdlEventHandler.h"
#include "../VSSharedData/VSSharedDataMainList.h"
#include "../VSInstance/VSInstance.h"

#include "../VSInstance/VSInstanceCreationData.h"

namespace VulkanSimplified
{
	Main::Main(const MainInitData& initData)
	{
		_internal = std::make_unique<VulkanSimplifiedInternal::MainInternal>(initData);
	}

	Main::~Main()
	{
	}

	Main::Main(Main&& rhs) noexcept : _internal(std::move(rhs._internal))
	{
	}

	Main& Main::operator=(Main&& rhs) noexcept
	{
		_internal = std::move(rhs._internal);
		return *this;
	}

	void Main::CreateInstance(const InstanceCreationData& instanceInit)
	{
		assert(_internal);
		_internal->CreateInstance(instanceInit);
	}

	SdlEventHandler Main::GetSdlEventHandler()
	{
		return _internal->GetSdlEventHandler();
	}

	SharedDataMainList Main::GetSharedDataMainList()
	{
		return _internal->GetSharedDataMainList();
	}

	Instance Main::GetInstance()
	{
		return _internal->GetInstance();
	}

	const SdlEventHandler Main::GetSdlEventHandler() const
	{
		return _internal->GetSdlEventHandler();
	}

	const SharedDataMainList Main::GetSharedDataMainList() const
	{
		return _internal->GetSharedDataMainList();
	}

	const Instance Main::GetInstance() const
	{
		return _internal->GetInstance();
	}

	VersionData Main::GetAppVersion() const
	{
		return _internal->GetAppVersion();
	}

	VersionData Main::GetMaxAvailableVulkanVersion() const
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
