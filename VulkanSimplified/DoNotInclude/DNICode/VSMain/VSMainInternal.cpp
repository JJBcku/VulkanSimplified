#include "VSMainNIpch.h"
#include "../../DNIHeaders/VSMain/VSMainInternal.h"

#include "../../../Include/VSMain/VSMainInitData.h"

#include "../../DNIHeaders/VSMain/EventHandler/SdlEventHandlerInternal.h"

#include "../../DNIHeaders/VSInstance/VSInstanceInternalCreationData.h"
#include "../../../Include/VSInstance/VSInstanceCreationData.h"

#include "../../DNIHeaders/VSSharedData/VSSharedDataMainListInternal.h"
#include "../../DNIHeaders/VSInstance/VSInstanceInternal.h"

#include "../../DNIHeaders/VSCommon/VSCStringsComparison.h"

namespace VulkanSimplified
{
	MainInternal::MainInternal(const MainInitData& initData) : _eventHandler(std::make_unique<SdlEventHandlerInternal>(initData.eventHandlerData)),
		_sharedData(std::make_unique<SharedDataMainListInternal>(initData.sharedDataCapabilities))
	{
		int result = SDL_Init(SDL_INIT_VIDEO);

		if (result < 0)
			throw std::runtime_error(SDL_GetError());

		result = SDL_Vulkan_LoadLibrary(nullptr);

		if (result < 0)
			throw std::runtime_error(SDL_GetError());

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

	void MainInternal::CreateInstance(const InstanceCreationData& instanceInit)
	{
		if (_instance)
			throw std::runtime_error("MainInternal::CreateInstance Error: Program tried to create the instance class twice!");

		InstanceInternalCreationData init;
		init.appName = instanceInit.appName + std::string(" ") + instanceInit.appVariantName;
		init.appVersion = instanceInit.appVersion.GetVulkanApiCompatibleVersion();
		init.engineName = instanceInit.engineName;
		init.engineVersion = instanceInit.engineVersion.GetVulkanApiCompatibleVersion();
		init.usedVulkanApiVersion = instanceInit.usedVulkanApiVersion;

		if (init.usedVulkanApiVersion < VersionData(0, 1, 0, 0))
			throw std::runtime_error("MainInternal::CreateInstance Error: Vulkan api version used must be 1.0.0 or later!");

		init.requestedExtensions = CompileRequestedInstanceExtensions(instanceInit.enabledExtensionPacks, _availableExtensionPacksList);
		init.requestedLayers = CompileRequestedInstanceLayers(instanceInit.enabledLayerPacks, _availableLayerPacksList);
		init.enabledExtensionPacksList = instanceInit.enabledExtensionPacks;
		init.enabledLayerPacksList = instanceInit.enabledLayerPacks;

		_instance = std::make_unique<InstanceInternal>(*_eventHandler, *_sharedData, init);
	}

	SdlEventHandlerInternal& MainInternal::GetSdlEventHandler()
	{
		return *_eventHandler;
	}

	SharedDataMainListInternal& MainInternal::GetSharedDataMainList()
	{
		return *_sharedData;
	}

	InstanceInternal& MainInternal::GetInstance()
	{
		assert(_instance);
		return *_instance;
	}

	const SdlEventHandlerInternal& MainInternal::GetSdlEventHandler() const
	{
		return *_eventHandler;
	}

	const SharedDataMainListInternal& MainInternal::GetSharedDataMainList() const
	{
		return *_sharedData;
	}

	const InstanceInternal& MainInternal::GetInstance() const
	{
		assert(_instance);
		return *_instance;
	}

	VersionData MainInternal::GetMaxAvailableVulkanVersion() const
	{
		return _maxApiVersion;
	}

	InstanceExtensionPacksList MainInternal::GetAvailableInstanceExtensionPacks() const
	{
		return _availableExtensionPacksList;
	}

	InstanceLayerPacksList MainInternal::GetAvailableInstanceLayerPacks() const
	{
		return _availableLayerPacksList;
	}

	uint32_t MainInternal::FindMaximumAvailableVulkanVersion() const
	{
#pragma warning(push)
#pragma warning(disable : 4191)

		uint32_t ret = 0;
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

	InstanceExtensionPacksList MainInternal::CompileAvailableInstanceExtensionPacks() const
	{
		InstanceExtensionPacksList ret;

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

	InstanceLayerPacksList MainInternal::CompileAvailableInstanceLayerPacks() const
	{
		InstanceLayerPacksList ret;

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

	std::vector<const char*> MainInternal::CompileRequestedInstanceExtensions(const InstanceExtensionPacksList& extensionPacksEnabled,
		const InstanceExtensionPacksList& extensionPacksAvailable) const
	{
		std::vector<const char*> ret;
		ret.reserve(sizeof(InstanceExtensionPacksList) * 16);

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

		std::stable_sort(ret.begin(), ret.end(), &ISFirstCStringLesser);
		ret.erase(std::unique(ret.begin(), ret.end(), &AreCStringEqual), ret.cend());

		ret.shrink_to_fit();
		return ret;
	}

	std::vector<const char*> MainInternal::CompileRequestedInstanceLayers(const InstanceLayerPacksList& layerPacksEnabled,
		const InstanceLayerPacksList& layerPacksAvailable) const
	{
		std::vector<const char*> ret;
		ret.reserve(sizeof(InstanceLayerPacksList) * 16);

		if (layerPacksEnabled.debugUtils)
		{
			if (layerPacksAvailable.debugUtils)
				ret.push_back("VK_LAYER_KHRONOS_validation");
			else
				throw std::runtime_error("MainInternal::CompileUsedInstanceExtensions Error: Program requested debug utils layers while they were not available!");
		}

		std::stable_sort(ret.begin(), ret.end(), &ISFirstCStringLesser);
		ret.erase(std::unique(ret.begin(), ret.end(), &AreCStringEqual), ret.cend());

		ret.shrink_to_fit();
		return ret;
	}

}
