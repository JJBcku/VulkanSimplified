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

	class VSMain
	{
	public:
		VSMain(const VSMainInitData& initData);
		~VSMain();

		SdlEventHandler GetSdlEventHandler();

		const SdlEventHandler GetSdlEventHandler() const;

	private:
		std::unique_ptr<VulkanSimplifiedInternal::VSMainInternal> _internal;
	};
}
