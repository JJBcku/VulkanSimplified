#pragma once

#include <memory>

struct VulkanBasicData;

struct VulkanData
{
	std::unique_ptr<VulkanBasicData> basicData;

	VulkanData();
	~VulkanData();
};