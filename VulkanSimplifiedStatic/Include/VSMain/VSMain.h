#pragma once

#include <memory>

namespace VulkanSimplifiedInternal
{
	class MainInternal;
}

namespace VulkanSimplified
{
	struct MainInitData;
	struct InstanceExtensionPacksList;
	struct InstanceLayerPacksList;

	class SdlEventHandler;

	class VulkanVersionData;

	class Main
	{
	public:
		Main(const MainInitData& initData);
		~Main();

		SdlEventHandler GetSdlEventHandler();

		const SdlEventHandler GetSdlEventHandler() const;

		VulkanVersionData GetAppVersion() const;
		VulkanVersionData GetMaxAvailableVulkanVersion() const;

		InstanceExtensionPacksList GetAvailableInstanceExtensionPacks() const;
		InstanceLayerPacksList GetAvailableInstanceLayerPacks() const;

	private:
		std::unique_ptr<VulkanSimplifiedInternal::MainInternal> _internal;
	};
}
