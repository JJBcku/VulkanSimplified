#include "VSInstanceDNIpch.h"
#include "VSDebugCallback.h"

#include <iostream>

namespace VulkanSimplified
{
	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void*)
	{
		std::cerr << callbackData->pMessage << std::endl;

		return VK_FALSE;
	}
}
