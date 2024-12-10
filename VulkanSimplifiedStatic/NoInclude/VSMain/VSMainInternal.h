#pragma once

#include "EventHandler/SdlEventHandlerInternal.h"

#include <string>

#include "../../Include/VSCommon/VulkanVersionData.h"

namespace VulkanSimplified
{
	struct VSMainInitData;

	class VulkanVersionData;
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

		VulkanSimplified::VulkanVersionData GetAppVersion() const;
		VulkanSimplified::VulkanVersionData GetMaxAvailableVulkanVersion() const;
		//InstanceExtensionList GetAvailableInstanceExtensions() const;

	private:
		std::string _appName;
		std::string _appVariantName;
		VulkanSimplified::VulkanVersionData _appVersion;
		std::string _engineName;
		VulkanSimplified::VulkanVersionData _engineVersion;

		VulkanSimplified::VulkanVersionData _maxApiVersion;

		SdlEventHandlerInternal _eventHandler;

		uint32_t FindMaximumAvailableVulkanVersion() const;
	};
}