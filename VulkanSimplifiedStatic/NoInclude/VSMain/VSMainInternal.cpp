#include "VSMainNIpch.h"
#include "VSMainInternal.h"

#include "../../Include/VSMain/VSMainInitData.h"

#include "../VSInstance/VSInstanceInitDataInternal.h"
#include "../../Include/VSInstance/VSInstanceInitData.h"

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

		{
			uint32_t size = 0;

			auto res = SDL_Vulkan_GetInstanceExtensions(nullptr, &size, nullptr);

			if (res == SDL_FALSE)
				throw std::runtime_error(SDL_GetError());

			if (size > 0)
			{
				_sdlRequired.resize(size);
				res = SDL_Vulkan_GetInstanceExtensions(nullptr, &size, _sdlRequired.data());

				if (res == SDL_FALSE)
					throw std::runtime_error(SDL_GetError());
			}
		}

		_availableExtensionPacksList = CompileAvailableInstanceExtensionPacks();
		_availableLayerPacksList = CompileAvailableInstanceLayerPacks();
	}

	MainInternal::~MainInternal()
	{
		SDL_Vulkan_UnloadLibrary();
		SDL_Quit();
	}

	void MainInternal::CreateInstance(const VulkanSimplified::InstanceInitData& instanceInit)
	{
		if (_instance.has_value())
			throw std::runtime_error("MainInternal::CreateInstance Error: Program tried to create the instance class twice!");

		InstanceInitDataInternal init;
		init.appName = _appName + _appVariantName;
		init.appVersion = _appVersion.GetVulkanApiCompatibleVersion();
		init.engineName = _engineName;
		init.engineVersion = _engineVersion.GetVulkanApiCompatibleVersion();
		init.usedVulkanApiVersion = instanceInit.usedVulkanApiVersion.GetVulkanApiCompatibleVersion();

		if (init.usedVulkanApiVersion < VK_API_VERSION_1_0)
			throw std::runtime_error("MainInternal::CreateInstance Error: Vulkan api version used must be 1.0.0 or later!");

		init.requestedExtensions = CompileRequestedInstanceExtensions(instanceInit.enabledExtensionPacks, _availableExtensionPacksList);
		init.requestedLayers = CompileRequestedInstanceLayers(instanceInit.enabledLayerPacks, _availableLayerPacksList);
		init.enabledExtensionPacksList = instanceInit.enabledExtensionPacks;
		init.enabledLayerPacksList = instanceInit.enabledLayerPacks;

		_instance.emplace(init);
	}

	SdlEventHandlerInternal& MainInternal::GetSdlEventHandler()
	{
		return _eventHandler;
	}

	InstanceInternal& MainInternal::GetInstance()
	{
		assert(_instance.has_value());
		return _instance.value();
	}

	const SdlEventHandlerInternal& MainInternal::GetSdlEventHandler() const
	{
		return _eventHandler;
	}

	const InstanceInternal& MainInternal::GetInstance() const
	{
		assert(_instance.has_value());
		return _instance.value();
	}

	VulkanSimplified::VersionData MainInternal::GetAppVersion() const
	{
		return _appVersion;
	}

	VulkanSimplified::VersionData MainInternal::GetMaxAvailableVulkanVersion() const
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

	bool MainInternal::CompareCStringPointers(const char* str1, const char* str2)
	{
		if (str1 == nullptr)
		{
			if (str2 == nullptr)
				return false;
			else
				return true;
		}
		else
		{
			if (str2 == nullptr)
				return false;
			else
			{
				int comp = std::strcmp(str1, str2);

				if (comp < 0)
					return true;
				else
					return false;
			}
		}
	}

	bool MainInternal::AreCStringPointersEqual(const char* str1, const char* str2)
	{
		if (str1 == str2)
			return true;
		else
		{
			if (str1 == nullptr || str2 == nullptr)
				return false;
			else
				return std::strcmp(str1, str2) == 0;
		}
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

		uint32_t size = 0;

		{
			vkEnumerateInstanceExtensionProperties(nullptr, &size, nullptr);
			availableExtensions.resize(size);
			vkEnumerateInstanceExtensionProperties(nullptr, &size, availableExtensions.data());
		}

		{

			if (!_sdlRequired.empty())
			{
				std::vector<bool> extensionsFound(_sdlRequired.size(), false);

				for (size_t i = 0; i < _sdlRequired.size(); ++i)
				{
					for (auto& extension : availableExtensions)
					{
						if (std::strcmp(extension.extensionName, _sdlRequired[i]) == 0)
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

	std::vector<const char*> MainInternal::CompileRequestedInstanceExtensions(const VulkanSimplified::InstanceExtensionPacksList& extensionPacksEnabled,
		const VulkanSimplified::InstanceExtensionPacksList& extensionPacksAvailable) const
	{
		std::vector<const char*> ret;
		ret.reserve(sizeof(VulkanSimplified::InstanceExtensionPacksList) * 16);

		if (extensionPacksEnabled.sdlRequiredExtensions)
		{
			if (extensionPacksAvailable.sdlRequiredExtensions)
			{
				ret.insert(ret.cend(), _sdlRequired.cbegin(), _sdlRequired.cend());
			} else
				throw std::runtime_error("MainInternal::CompileUsedInstanceExtensions Error: Program requested sdl2 required extensions while they were not available!");
		}

		if (extensionPacksEnabled.debugUtils)
		{
			if (extensionPacksAvailable.debugUtils)
				ret.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			else
				throw std::runtime_error("MainInternal::CompileUsedInstanceExtensions Error: Program requested debug utils extensions while they were not available!");
		}

		std::stable_sort(ret.begin(), ret.end(), &MainInternal::CompareCStringPointers);
		ret.erase(std::unique(ret.begin(), ret.end(), &MainInternal::AreCStringPointersEqual), ret.cend());

		ret.shrink_to_fit();
		return ret;
	}

	std::vector<const char*> MainInternal::CompileRequestedInstanceLayers(const VulkanSimplified::InstanceLayerPacksList& layerPacksEnabled,
		const VulkanSimplified::InstanceLayerPacksList& layerPacksAvailable) const
	{
		std::vector<const char*> ret;
		ret.reserve(sizeof(VulkanSimplified::InstanceLayerPacksList) * 16);

		if (layerPacksEnabled.debugUtils)
		{
			if (layerPacksAvailable.debugUtils)
				ret.push_back("VK_LAYER_KHRONOS_validation");
			else
				throw std::runtime_error("MainInternal::CompileUsedInstanceExtensions Error: Program requested debug utils layers while they were not available!");
		}

		std::stable_sort(ret.begin(), ret.end(), &MainInternal::CompareCStringPointers);
		ret.erase(std::unique(ret.begin(), ret.end(), &MainInternal::AreCStringPointersEqual), ret.cend());

		ret.shrink_to_fit();
		return ret;
	}

}
