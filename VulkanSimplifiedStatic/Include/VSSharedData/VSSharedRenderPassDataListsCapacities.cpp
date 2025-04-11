#include "VSSharedIpch.h"
#include "VSSharedRenderPassDataListsCapacities.h"

namespace VulkanSimplified
{
	SharedRenderPassDataListsCapacities::SharedRenderPassDataListsCapacities()
	{
		sharedRenderPassAttachmentsInitialCapacity = 0;
		sharedRenderPassReferencesInitialCapacity = 0;
		sharedSubpassDependenciesInitialCapacity = 0;

		doubleColorClearValueInitialCapacity = 0;
		int64ColorClearValueInitialCapacity = 0;
		uint64ColorClearValueInitialCapacity = 0;

		floatColorClearValueInitialCapacity = 0;
		intColorClearValueInitialCapacity = 0;
		uintColorClearValueInitialCapacity = 0;

		depthStencilColorClearValueInitialCapacity = 0;
	}
}