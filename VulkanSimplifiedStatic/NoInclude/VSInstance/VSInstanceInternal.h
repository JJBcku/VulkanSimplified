#pragma once

#include "../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../Include/VSMain/VSInstanceLayerPacksList.h"

namespace VulkanSimplifiedInternal
{
	struct InstanceInitDataInternal;

	class InstanceInternal
	{
	public:
		InstanceInternal(const InstanceInitDataInternal& initData);
		~InstanceInternal();

		InstanceInternal(const InstanceInternal&) noexcept = delete;
		InstanceInternal(InstanceInternal&&) noexcept = delete;

		InstanceInternal& operator=(const InstanceInternal&) noexcept = delete;
		InstanceInternal& operator=(InstanceInternal&&) noexcept = delete;

	private:
		VkInstance _instance;
		VkDebugUtilsMessengerEXT _debugMessenger;

		VulkanSimplified::InstanceExtensionPacksList _enabledExtensionPacksList;
		VulkanSimplified::InstanceLayerPacksList _enabledLayerPacksList;
	};
}