#pragma once

#include <VSMainDef.h>

struct VulkanBasicData
{
	std::unique_ptr<VS::Main> vsmain;

	VulkanBasicData(const VulkanBasicData&) noexcept = delete;

	VulkanBasicData& operator=(const VulkanBasicData&) noexcept = delete;

	VulkanBasicData();
	~VulkanBasicData();
};