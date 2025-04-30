#pragma once

#include "VSMemoryAllocationFullID.h"

namespace VulkanSimplified
{
	typedef size_t SubAllocationBeggining;
	typedef std::pair<MemoryAllocationFullID, SubAllocationBeggining> MemorySuballocationFullID;
}