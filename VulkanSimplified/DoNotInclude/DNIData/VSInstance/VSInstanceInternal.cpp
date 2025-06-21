#include "VSInstanceDNIpch.h"
#include "VSInstanceInternal.h"

#include "VSInstanceInternalCreationData.h"
#include "VSDebugCallback.h"

#include "VSPhysicalDeviceDataInternal.h"
#include "../VSDevice/VSDeviceMainInternal.h"

#include "../../../Include/VSInstance/VSLogicalDeviceCreateInfo.h"
#include "VsLogicalDeviceInternalCreationData.h"

#include "../../../Include/VSDevice/VSDeviceInitialCapacitiesList.h"

namespace VulkanSimplified
{
	InstanceInternal::InstanceInternal(SdlEventHandlerInternal& eventHandler, const SharedDataMainListInternal& sharedDataMain, const InstanceInternalCreationData& initData) :
		_eventHandler(eventHandler), _sharedDataMain(sharedDataMain)
	{
		_instance = VK_NULL_HANDLE;
		_debugMessenger = VK_NULL_HANDLE;

		_appName = initData.appName;
		_appVersion = initData.appVersion;
		_padding = 0;
		_engineName = initData.engineName;
		_engineVersion = initData.engineVersion;
		_usedVulkanApiVersion = initData.usedVulkanApiVersion.GetVulkanApiCompatibleVersion();

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = _appName.c_str();
		appInfo.applicationVersion = _appVersion.GetVulkanApiCompatibleVersion();
		appInfo.pEngineName = _engineName.c_str();
		appInfo.engineVersion = _engineVersion.GetVulkanApiCompatibleVersion();
		appInfo.apiVersion = _usedVulkanApiVersion;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = static_cast<uint32_t>(initData.requestedLayers.size());
		createInfo.ppEnabledLayerNames = initData.requestedLayers.data();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(initData.requestedExtensions.size());
		createInfo.ppEnabledExtensionNames = initData.requestedExtensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugInfo{};

		if (initData.enabledExtensionPacksList.debugUtils && initData.enabledLayerPacksList.debugUtils)
		{
			debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugInfo.pfnUserCallback = debugCallback;
			debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
			debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
			debugInfo.flags = 0;
			debugInfo.pNext = nullptr;
			debugInfo.pUserData = nullptr;

			createInfo.pNext = &debugInfo;
		}

		if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Error: Program failed to create vulkan instance!");
		}

		if (initData.enabledExtensionPacksList.debugUtils && initData.enabledLayerPacksList.debugUtils)
		{
#pragma warning(push)
#pragma warning(disable : 4191)
			auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT"));
#pragma warning(pop)

			if (func == nullptr)
				throw std::runtime_error("Error: Program failed to find vkCreateDebugUtilsMessengerEXT function pointer!");

			if (func == nullptr || func(_instance, &debugInfo, nullptr, &_debugMessenger) != VK_SUCCESS)
			{
				throw std::runtime_error("Error: Program failed to create a debug messenger!");
			}
		}

		_enabledExtensionPacksList = initData.enabledExtensionPacksList;
		_enabledLayerPacksList = initData.enabledLayerPacksList;

		EnumerateDevices();
	}

	InstanceInternal::~InstanceInternal()
	{
		_usedDevice.reset();

		if (_debugMessenger != VK_NULL_HANDLE)
		{
#pragma warning(push)
#pragma warning(disable : 4191)
			auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT"));
#pragma warning(pop)

			if (func != nullptr)
				func(_instance, _debugMessenger, nullptr);
		}

		if (_instance != VK_NULL_HANDLE)
		{
			vkDestroyInstance(_instance, nullptr);
		}
	}

	void InstanceInternal::EnumerateDevices()
	{
		uint32_t size = 0;
		std::vector<VkPhysicalDevice> physicalDevices;

		auto result = vkEnumeratePhysicalDevices(_instance, &size, nullptr);

		if (result == VK_SUCCESS && size > 0)
		{
			physicalDevices.resize(size);
			_availableDevices.reserve(size);

			result = vkEnumeratePhysicalDevices(_instance, &size, physicalDevices.data());

			if (result != VK_SUCCESS)
				throw std::runtime_error("DeviceListInternal::EnumeratePhysicalDevices Error: Program failed to enumerate physical devices!");

			VkSurfaceKHR testSurface = VK_NULL_HANDLE;
			SDL_Window* testWindow = nullptr;

			if (_enabledExtensionPacksList.sdlRequiredExtensions)
			{
				Uint32 windowFlags = SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS;

				testWindow = SDL_CreateWindow("Device Enumeration Window!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, windowFlags);

				if (testWindow == nullptr)
					throw std::runtime_error("DeviceListInternal::EnumeratePhysicalDevices Error: Program failed to create a window!");

				if (SDL_Vulkan_CreateSurface(testWindow, _instance, &testSurface) != SDL_TRUE)
					throw std::runtime_error("DeviceListInternal::EnumeratePhysicalDevices Error: Program failed to create a window's surface!");
			}

			for (auto& device : physicalDevices)
			{
				_availableDevices.emplace_back(device, testSurface);
			}

			if (testSurface != VK_NULL_HANDLE)
			{
				vkDestroySurfaceKHR(_instance, testSurface, nullptr);
				SDL_DestroyWindow(testWindow);
			}
		}
		else
		{
			throw std::runtime_error("DeviceListInternal::EnumeratePhysicalDevices Error: Program failed to find any Vulkan compatible devices!");
		}
	}

	const std::string& InstanceInternal::GetAppFullName() const
	{
		return _appName;
	}

	const std::string& InstanceInternal::GetEngineFullName() const
	{
		return _engineName;
	}

	VersionData InstanceInternal::GetAppVersion() const
	{
		return _appVersion;
	}

	VersionData InstanceInternal::GetEngineVersion() const
	{
		return _engineVersion;
	}

	size_t InstanceInternal::GetAvailableDevicesCount() const
	{
		return _availableDevices.size();
	}

	PhysicalDeviceDataInternal& InstanceInternal::GetPhysicalDeviceData(size_t deviceIndex)
	{
		if (deviceIndex >= _availableDevices.size())
			throw std::runtime_error("InstanceInternal::GetPhysicalDeviceData Error: Program tried to read past the end of the list");

		return _availableDevices[deviceIndex];
	}

	DeviceMainInternal& InstanceInternal::GetChoosenDevicesMainClass()
	{
		if (_usedDevice)
			return *_usedDevice;
		else
			throw std::runtime_error("InstanceInternal::GetChoosenDevicesMainClass Error: Program tried to access a non-existent logical devices main class!");
	}

	const PhysicalDeviceDataInternal& InstanceInternal::GetPhysicalDeviceData(size_t deviceIndex) const
	{
		if (deviceIndex >= _availableDevices.size())
			throw std::runtime_error("InstanceInternal::GetPhysicalDeviceData Const Error: Program tried to read past the end of the list");

		return _availableDevices[deviceIndex];
	}

	const DeviceMainInternal& InstanceInternal::GetChoosenDevicesMainClass() const
	{
		if (_usedDevice)
			return *_usedDevice;
		else
			throw std::runtime_error("InstanceInternal::GetChoosenDevicesMainClass Const Error: Program tried to access a non-existent logical devices main class!");
	}

	void InstanceInternal::CreateLogicalDevice(const LogicalDeviceCreationData& creationData, const DeviceInitialCapacitiesList& initialCapacities)
	{
		if (_usedDevice)
			throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Program support only up to one logical device at one time!");

		if (creationData.physicalGPUIndex >= _availableDevices.size())
			throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Program tried to read past the end of the available devices list!");

		if (creationData.queuesCreationInfo.empty())
			throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Program tried to create device with no queues!");

		if (creationData.queuesCreationInfo.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Queue creation info list is bigger than allowed!");

		const auto& physicalDeviceData = _availableDevices[creationData.physicalGPUIndex];

		LogicalDeviceInternalCreationData internalCreationData;
		internalCreationData.queueInfos.reserve(creationData.queuesCreationInfo.size());

		std::vector<std::vector<float>> queuePrioritiesList(creationData.queuesCreationInfo.size(), {});
		{
			auto& queueFamiliesData = physicalDeviceData.GetVulkanQueueFamiliesData();
			size_t totalQueueCount = 0;

			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

			for (size_t i = 0; i < creationData.queuesCreationInfo.size(); ++i)
			{
				auto& queueData = creationData.queuesCreationInfo[i];

				if (queueData.queuesFamily >= queueFamiliesData.size())
					throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Program tried to create queues on non-existent family!");

				if (queueData.queuesPriorities.empty())
					throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Queue priorities list must not be empty!");

				if (queueData.queuesPriorities.size() > queueFamiliesData[queueData.queuesFamily].queueCount)
					throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Program tried to create more queues than the queues family allow");

				if (totalQueueCount + queueData.queuesPriorities.size() < totalQueueCount)
					throw std::runtime_error("InstanceInternal::CreateLogicalDevice Error: Total queue count overflowed!");

				totalQueueCount += queueData.queuesPriorities.size();

				queueInfo.queueFamilyIndex = queueData.queuesFamily;
				queueInfo.queueCount = static_cast<uint32_t>(queueData.queuesPriorities.size());

				queuePrioritiesList[i].reserve(queueData.queuesPriorities.size());
				for (size_t j = 0; j < queueData.queuesPriorities.size(); ++j)
				{
					float priority = static_cast<float>(queueData.queuesPriorities[j]) / static_cast<float>(std::numeric_limits<uint16_t>::max());
					queuePrioritiesList[i].push_back(priority);
				}

				queueInfo.pQueuePriorities = queuePrioritiesList[i].data();

				internalCreationData.queueInfos.push_back(queueInfo);
			}
		}

		auto& vulkan10Properties = physicalDeviceData.GetVulkan10Properties();
		internalCreationData.apiVersion = std::min(_usedVulkanApiVersion, vulkan10Properties.apiMaxSupportedVersion);

		internalCreationData.features = PhysicalDeviceDataInternal::CompileDevicesRequestedVulkan10Features(creationData.vulkan10EnabledFeatures);
		internalCreationData.enabledExtensionsList = PhysicalDeviceDataInternal::CompileDevicesRequestedExtensionList(creationData.requestedExtensionPacks);

		internalCreationData.vulkan10EnabledFeatures = creationData.vulkan10EnabledFeatures;
		internalCreationData.requestedExtensionPacks = creationData.requestedExtensionPacks;

		_usedDevice = std::make_unique<DeviceMainInternal>(_eventHandler, _sharedDataMain, _instance, internalCreationData, physicalDeviceData, initialCapacities);
	}

}