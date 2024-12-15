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

	struct InstanceInitData;

	class SdlEventHandler;
	class Instance;

	class VersionData;

	class Main
	{
	public:
		Main(const MainInitData& initData);
		~Main();

		Main(const Main&) noexcept = delete;
		Main(Main&& rhs) noexcept;

		Main& operator=(const Main&) noexcept = delete;
		Main& operator=(Main&& rhs) noexcept;

		void CreateInstance(const InstanceInitData& instanceInit);

		SdlEventHandler GetSdlEventHandler();
		Instance GetInstance();

		const SdlEventHandler GetSdlEventHandler() const;
		const Instance GetInstance() const;

		VersionData GetAppVersion() const;
		VersionData GetMaxAvailableVulkanVersion() const;

		InstanceExtensionPacksList GetAvailableInstanceExtensionPacks() const;
		InstanceLayerPacksList GetAvailableInstanceLayerPacks() const;

	private:
		std::unique_ptr<VulkanSimplifiedInternal::MainInternal> _internal;
	};
}
