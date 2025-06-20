#pragma once

#include <VSMainDef.h>

struct VulkanBasicData
{
	std::unique_ptr<VS::Main> vsmain;

	VulkanBasicData();
	~VulkanBasicData();
};