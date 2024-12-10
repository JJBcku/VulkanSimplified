#pragma once

#include <memory>

namespace VulkanSimplifiedInternal
{
	class VSMainInternal;
}

namespace VulkanSimplified
{
	struct VSMainInitData;

	class SdlEventHandler;

	class VulkanVersionData;

	class VSMain
	{
	public:
		VSMain(const VSMainInitData& initData);
		~VSMain();

		SdlEventHandler GetSdlEventHandler();

		const SdlEventHandler GetSdlEventHandler() const;

		VulkanVersionData GetAppVersion() const;
		VulkanVersionData GetMaxAvailableVulkanVersion() const;

	private:
		std::unique_ptr<VulkanSimplifiedInternal::VSMainInternal> _internal;
	};
}
