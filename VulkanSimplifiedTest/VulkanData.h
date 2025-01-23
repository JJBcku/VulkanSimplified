#pragma once

#include <memory>

struct VulkanBasicData;
struct VulkanInstanceData;

struct VulkanData
{
	std::unique_ptr<VulkanBasicData> basicData;
	std::unique_ptr<VulkanInstanceData> instanceData;

	VulkanData();
	~VulkanData();
};