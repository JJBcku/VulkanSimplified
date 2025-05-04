#pragma once

#include <VSMainDef.h>

struct VulkanBasicData
{
	std::unique_ptr<VulkanSimplified::Main> vsmain;

	VulkanBasicData();
	~VulkanBasicData();
};