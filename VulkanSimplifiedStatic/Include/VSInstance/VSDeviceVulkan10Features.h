#pragma once

namespace VulkanSimplified
{
	typedef uint64_t DeviceVulkan10FeatureFlags;

	enum DeviceVulkan10FeaturesFlagBits : DeviceVulkan10FeatureFlags
	{
		DEVICE_VULKAN10_FEATURE_FULL_DRAW_INDEX_UINT32 = 0x1,
		DEVICE_VULKAN10_FEATURE_INDEPENDENT_BLEND = 0x2,
		DEVICE_VULKAN10_FEATURE_FILL_MODE_NONSOLID = 0x4,
		DEVICE_VULKAN10_FEATURE_SAMPLER_ANISOTROPY = 0x8,
		DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ETC2 = 0x10,
		DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_ASTC_LDR = 0x20,
		DEVICE_VULKAN10_FEATURE_TEXTURE_COMPRESSION_BC = 0x40,
		DEVICE_VULKAN10_FEATURE_SHADER_FLOAT64 = 0x80,
		DEVICE_VULKAN10_FEATURE_SHADER_INT64 = 0x100,
		DEVICE_VULKAN10_FEATURE_SHADER_INT16 = 0x200,
		DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_RESIDENCY = 0x400,
		DEVICE_VULKAN10_FEATURE_SHADER_RESOURCE_MINIMUM_LOD = 0x800,
	};
}