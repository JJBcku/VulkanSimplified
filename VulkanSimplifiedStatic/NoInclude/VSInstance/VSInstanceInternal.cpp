#include "VSInstanceNIpch.h"
#include "VSInstanceInternal.h"

#include "VSInstanceInitDataInternal.h"
#include "VSDebugCallback.h"

namespace VulkanSimplifiedInternal
{
	InstanceInternal::InstanceInternal(const InstanceInitDataInternal& initData)
	{
		_instance = VK_NULL_HANDLE;
		_debugMessenger = VK_NULL_HANDLE;

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = initData.appName.c_str();
		appInfo.applicationVersion = initData.appVersion;
		appInfo.pEngineName = initData.engineName.c_str();
		appInfo.engineVersion = initData.engineVersion;
		appInfo.apiVersion = initData.usedVulkanApiVersion;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = static_cast<std::uint32_t>(initData.requestedLayers.size());
		createInfo.ppEnabledLayerNames = initData.requestedLayers.data();
		createInfo.enabledExtensionCount = static_cast<std::uint32_t>(initData.requestedExtensions.size());
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
	}

	InstanceInternal::~InstanceInternal()
	{
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

}