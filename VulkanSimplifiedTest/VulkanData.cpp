#include "pch.h"
#include "VulkanData.h"

#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanDeviceDependentData.h"

VulkanData::VulkanData() : basicData(), instanceDependentData(), deviceDependentData()
{
}

VulkanData::~VulkanData()
{
}
