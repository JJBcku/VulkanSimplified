#include "VSInstanceIpch.h"
#include "VSInstance.h"

#include "../../NoInclude/VSInstance/VSInstanceInternal.h"

namespace VulkanSimplified
{
	Instance::Instance(VulkanSimplifiedInternal::InstanceInternal& ref) : _internal(ref)
	{
	}

	Instance::~Instance()
	{
	}

}
