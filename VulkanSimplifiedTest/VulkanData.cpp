#include "pch.h"
#include "VulkanData.h"

#include "VulkanBasicData.h"
#include "VulkanSharedData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanDeviceDependentData.h"
#include "VulkanRenderPassData.h"
#include "VulkanPipelineData.h"

VulkanData::VulkanData() : basicData(), sharedData(), instanceDependentData(), deviceDependentData(), renderPassData(), pipelineData()
{
}

VulkanData::~VulkanData()
{
}
