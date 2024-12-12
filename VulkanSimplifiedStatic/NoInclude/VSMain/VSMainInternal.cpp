#include "VSMainNIpch.h"
#include "VSMainInternal.h"

#include "../../Include/VSMain/VSMainInitData.h"

namespace VulkanSimplifiedInternal
{
	MainInternal::MainInternal(const VulkanSimplified::MainInitData& initData) : _eventHandler(initData.eventHandlerData)
	{
		int result = SDL_Init(SDL_INIT_VIDEO);

		if (result < 0)
			throw std::runtime_error(SDL_GetError());

		result = SDL_Vulkan_LoadLibrary(nullptr);

		if (result < 0)
			throw std::runtime_error(SDL_GetError());

		_appName = initData.appName;
		_appVariantName = initData.appVariantName;
		_appVersion = initData.appVersion;
		_engineName = initData.engineName;
		_engineVersion = initData.engineVersion;

		_maxApiVersion = FindMaximumAvailableVulkanVersion();

		_availableExtensionPacksList = CompileAvailableInstanceExtensionPacks();
		_availableLayerPacksList = CompileAvailableInstanceLayerPacks();
	}

	MainInternal::~MainInternal()
	{
		SDL_Vulkan_UnloadLibrary();
		SDL_Quit();
	}

	SdlEventHandlerInternal& MainInternal::GetSdlEventHandler()
	{
		return _eventHandler;
	}

	const SdlEventHandlerInternal& MainInternal::GetSdlEventHandler() const
	{
		return _eventHandler;
	}

	VulkanSimplified::VulkanVersionData MainInternal::GetAppVersion() const
	{
		return _appVersion;
	}

	VulkanSimplified::VulkanVersionData MainInternal::GetMaxAvailableVulkanVersion() const
	{
		return _maxApiVersion;
	}

	VulkanSimplified::InstanceExtensionPacksList MainInternal::GetAvailableInstanceExtensionPacks() const
	{
		return _availableExtensionPacksList;
	}

	VulkanSimplified::InstanceLayerPacksList MainInternal::GetAvailableInstanceLayerPacks() const
	{
		return _availableLayerPacksList;
	}

	uint32_t MainInternal::FindMaximumAvailableVulkanVersion() const
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
				throw std::runtime_error("MainInternal::FindMaximumAvailableVulkanVersios Errror: Program failed to enumerate max available vulkan api version!");
		}

		return ret;
	}

	VulkanSimplified::InstanceExtensionPacksList MainInternal::CompileAvailableInstanceExtensionPacks() const
	{
		VulkanSimplified::InstanceExtensionPacksList ret;

		std::vector<VkExtensionProperties> availableExtensions;
		std::vector<const char*> sdlRequired;

		uint32_t size = 0;

		{
			vkEnumerateInstanceExtensionProperties(nullptr, &size, nullptr);
			availableExtensions.resize(size);
			vkEnumerateInstanceExtensionProperties(nullptr, &size, availableExtensions.data());
		}

		{
			size = 0;
			auto res = SDL_Vulkan_GetInstanceExtensions(nullptr, &size, nullptr);

			if (res == SDL_FALSE)
				throw std::runtime_error(SDL_GetError());

			if (size != 0)
			{
				sdlRequired.resize(size);
				res = SDL_Vulkan_GetInstanceExtensions(nullptr, &size, sdlRequired.data());

				if (res == SDL_FALSE)
					throw std::runtime_error(SDL_GetError());

				std::vector<bool> extensionsFound(size, false);

				for (size_t i = 0; i < sdlRequired.size(); ++i)
				{
					for (auto& extension : availableExtensions)
					{
						if (std::strcmp(extension.extensionName, sdlRequired[i]) == 0)
						{
							extensionsFound[i] = true;
							break;
						}
					}
				}

				bool foundAll = true;
				for (size_t i = 0; i < extensionsFound.size(); ++i)
				{
					if (!extensionsFound[i])
					{
						foundAll = false;
						break;
					}
				}

				ret.sdlRequiredExtensions = foundAll;
			}
		}

		{
			for (auto& extension : availableExtensions)
			{
				if (std::strcmp(extension.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0)
				{
					ret.debugUtils = true;
					break;
				}
			}
		}

		return ret;
	}

	VulkanSimplified::InstanceLayerPacksList MainInternal::CompileAvailableInstanceLayerPacks() const
	{
		VulkanSimplified::InstanceLayerPacksList ret;

		std::vector<VkLayerProperties> availableLayers;

		{
			uint32_t data = 0;
			vkEnumerateInstanceLayerProperties(&data, nullptr);
			availableLayers.resize(data);

			vkEnumerateInstanceLayerProperties(&data, availableLayers.data());
		}

		for (auto& layer : availableLayers)
		{
			if (std::strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0)
			{
				ret.debugUtils = true;
				break;
			}
		}

		return ret;
	}

}
