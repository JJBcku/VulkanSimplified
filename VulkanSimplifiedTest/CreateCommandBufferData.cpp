#include "pch.h"
#include "CreateCommandBufferData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanCommandBufferData.h"

#include "SwapchainSizes.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSDeviceCore.h>
#include <VSCommandPoolMainList.h>
#include <VSCommandPoolQFGroupList.h>
#include <VSIRCommandPool.h>

#include <VSCommandPoolQFGroupListsInitialCapacities.h>

void CreateCommandBufferData(VulkanData& data)
{
	data.commandBufferData = std::make_unique<VulkanCommandBufferData>();
	auto& instData = *data.instanceDependentData;
	auto& bufferData = *data.commandBufferData;

	auto deviceMain = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto deviceCore = deviceMain.GetDeviceCore();
	auto commandPoolMain = deviceMain.GetCommandPoolMainList();

	VS::CommandPoolQFGroupListsInitialCapacities qfInit;
	qfInit.individualResetCommandPoolListInitialReservation = 3;

	{
		bufferData.graphicGroup = commandPoolMain.AddQueueFamiliesPoolGroup(instData.graphicsQueueFamily, qfInit, 3);

		if (instData.transferOnlyQueueFamily.has_value())
		{
			bufferData.transferGroup = commandPoolMain.AddQueueFamiliesPoolGroup(instData.transferOnlyQueueFamily.value(), qfInit, 2);
		}

		if (instData.presentingQueueFamily.has_value())
		{
			if (instData.transferOnlyQueueFamily.has_value() && instData.transferOnlyQueueFamily.value() == instData.presentingQueueFamily.value())
			{
				bufferData.presentGroup = bufferData.transferGroup;
			}
			else
			{
				bufferData.presentGroup = commandPoolMain.AddQueueFamiliesPoolGroup(instData.presentingQueueFamily.value(), qfInit, 1);
			}
		}
	}

	{
		auto graphicGroup = commandPoolMain.GetQueueFamiliesPoolGroup(bufferData.graphicGroup);
		bufferData.graphicPool = graphicGroup.AddCommandPoolWithIndividualReset(true, instData.graphicsQueueIndex, framesInFlight, 0);

		auto graphicPool = graphicGroup.GetCommandPoolWithIndividualReset(bufferData.graphicPool);
		bufferData.graphicBuffers = graphicPool.AllocatePrimaryCommandBuffers(framesInFlight, framesInFlight);

		if (bufferData.transferGroup.has_value())
		{
			auto transferGroup = commandPoolMain.GetQueueFamiliesPoolGroup(bufferData.transferGroup.value());
			bufferData.transferPool = transferGroup.AddCommandPoolWithIndividualReset(true, instData.transferOnlyQueueIndex.value(), framesInFlight, 0);

			auto transferPool = transferGroup.GetCommandPoolWithIndividualReset(bufferData.transferPool.value());
			bufferData.transferBuffers = transferPool.AllocatePrimaryCommandBuffers(framesInFlight, framesInFlight);
		}

		if (bufferData.presentGroup.has_value())
		{
			if (bufferData.transferGroup.has_value() && bufferData.transferGroup.value() == bufferData.presentGroup.value())
			{
				bufferData.presentPool = bufferData.transferPool;
				bufferData.presentBuffers = bufferData.transferBuffers;
			}
			else
			{
				auto presentGroup = commandPoolMain.GetQueueFamiliesPoolGroup(bufferData.presentGroup.value());
				bufferData.presentPool = presentGroup.AddCommandPoolWithIndividualReset(true, instData.presentingQueueIndex.value(), framesInFlight, 0);

				auto presentPool = presentGroup.GetCommandPoolWithIndividualReset(bufferData.presentPool.value());
				bufferData.presentBuffers = presentPool.AllocatePrimaryCommandBuffers(framesInFlight, framesInFlight);
			}
		}
	}
}
