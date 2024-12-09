#include "pch.h"
#include "CreateBasicData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"

#include "VSMain.h"
#include "VSMainInitData.h"

void CreateBasicData(VulkanData& data)
{
	data.basicData = std::make_unique<VulkanBasicData>();
	
	VSMainInitData basicInit;

	data.basicData->vsmain.emplace(basicInit);
}
