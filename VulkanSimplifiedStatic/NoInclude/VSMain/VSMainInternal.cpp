#include "VSMainNIpch.h"
#include "VSMainInternal.h"

#include "../../Include/VSMain/VSMainInitData.h"

namespace VulkanSimplifiedInternal
{
	VSMainInternal::VSMainInternal(const VulkanSimplified::VSMainInitData& initData) : _eventHandler(initData.eventHandlerData)
	{
		int result = SDL_InitSubSystem(SDL_INIT_VIDEO);

		if (result < 0)
			throw std::runtime_error("Program failed to initialize SDL!");

		_appName = initData.appName;
		_appVariantName = initData.appVariantName;
		_appVersion = initData.appVersion;
		_engineName = initData.engineName;
		_engineVersion = initData.engineVersion;

		_maxApiVersion = FindMaximumAvailableVulkanVersion();
	}

	VSMainInternal::~VSMainInternal()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		SDL_Quit();
	}

	SdlEventHandlerInternal& VSMainInternal::GetSdlEventHandler()
	{
		return _eventHandler;
	}

	const SdlEventHandlerInternal& VSMainInternal::GetSdlEventHandler() const
	{
		return _eventHandler;
	}

	VulkanSimplified::VulkanVersionData VSMainInternal::GetAppVersion() const
	{
		return _appVersion;
	}

	VulkanSimplified::VulkanVersionData VSMainInternal::GetMaxAvailableVulkanVersion() const
	{
		return _maxApiVersion;
	}

	uint32_t VSMainInternal::FindMaximumAvailableVulkanVersion() const
	{
#pragma warning(push)
#pragma warning(disable : 4191)

		std::uint32_t ret = 0;
		auto func = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(NULL, "vkEnumerateInstanceVersion"));
#pragma warning(pop)

		if (func == NULL)
		{
			ret = VK_API_VERSION_1_0;
		}
		else
		{
			if (func(&ret) != VK_SUCCESS)
				throw std::runtime_error("VSMainInternal::FindMaximumAvailableVulkanVersios Errror: Program failed to enumerate max available vulkan api version!");
		}

		return ret;
	}

}
