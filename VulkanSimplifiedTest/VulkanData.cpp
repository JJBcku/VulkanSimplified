#include "pch.h"
#include "VulkanData.h"

#include "VulkanBasicData.h"
#include "VulkanSharedData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanDeviceDependentData.h"

VulkanData::VulkanData() : basicData(), sharedData(), instanceDependentData(), deviceDependentData()
{
}

VulkanData::~VulkanData()
{
}
