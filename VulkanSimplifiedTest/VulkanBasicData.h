#pragma once

#include <optional>

#include "VSMain.h"

struct VulkanBasicData
{
	std::optional<VulkanSimplified::Main> vsmain;

	VulkanBasicData();
	~VulkanBasicData();
};