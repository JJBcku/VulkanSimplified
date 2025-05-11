#include "VSDeviceNIpch.h"
#include "VSCommandPoolQFGroupListInternal.h"

#include "VSDeviceCoreInternal.h"

#include "../../Include/VSDevice/VSCommandPoolQFGroupListsInitialCapacities.h"
#include "../../Include/VSDevice/VSCommandBufferSubmissionData.h"
#include "../../Include/VSDevice/VSCommandBufferGenericID.h"

#include "VSNIRCommandPoolInternal.h"
#include "VSIRCommandPoolInternal.h"
#include "VSSynchronizationDataListsInternal.h"

#include "VSPrimaryNIRCommandBufferInternal.h"
#include "VSPrimaryIRCommandBufferInternal.h"

#include "VSSecondaryNIRCommandBufferInternal.h"
#include "VSSecondaryIRCommandBufferInternal.h"

#include "../VSCommon/VSPipelineStageFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	CommandPoolQFGroupListInternal::CommandPoolQFGroupListInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, size_t queueFamily,
		const VulkanSimplified::CommandPoolQFGroupListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _deviceRenderPassData(deviceRenderPassData),
		_sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList),
		_dataBufferList(dataBufferList), _windowList(windowList), _device(_deviceCore.GetDevice()), _queueFamily(queueFamily),
		_noIndividualResetCommandPoolList(initialCapacities.noIndividualResetCommandPoolListInitialReservation),
		_individualResetCommandPoolList(initialCapacities.individualResetCommandPoolListInitialReservation)
	{
	}

	CommandPoolQFGroupListInternal::~CommandPoolQFGroupListInternal()
	{
	}

	IDObject<VulkanSimplified::NIRPoolPointer> CommandPoolQFGroupListInternal::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving)
	{
		VkCommandPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		createInfo.queueFamilyIndex = _deviceCore.GetQueuesFamily(queueID);

		if (frequentlyRedoneBuffers)
			createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

		if (createInfo.queueFamilyIndex != _queueFamily)
			throw std::runtime_error("CommandPoolQFGroupListInternal::AddCommandPoolWithoutIndividualReset Error: Program tried to use queue from a different family!");

		VkCommandPool add = VK_NULL_HANDLE;

		if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("CommandPoolQFGroupListInternal::AddCommandPoolWithoutIndividualReset Error: Program failed to create a command pool!");

		return _noIndividualResetCommandPoolList.AddObject(std::make_unique<NIRCommandPoolInternal>(_deviceCore, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _dataBufferList, _windowList, _device, add, _deviceCore.GetQueue(queueID),
			primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity), addOnReserving);
	}

	IDObject<VulkanSimplified::IRPoolPointer> CommandPoolQFGroupListInternal::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving)
	{
		VkCommandPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		createInfo.queueFamilyIndex = _deviceCore.GetQueuesFamily(queueID);
		createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		if (frequentlyRedoneBuffers)
			createInfo.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

		if (createInfo.queueFamilyIndex != _queueFamily)
			throw std::runtime_error("CommandPoolQFGroupListInternal::AddCommandPoolWithIndividualReset Error: Program tried to use queue from a different family!");

		VkCommandPool add = VK_NULL_HANDLE;

		if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("CommandPoolQFGroupListInternal::AddCommandPoolWithIndividualReset Error: Program failed to create a command pool!");

		return _individualResetCommandPoolList.AddObject(std::make_unique<IRCommandPoolInternal>(_deviceCore, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
			_synchronizationList, _imageList, _dataBufferList, _windowList, _device, add, _deviceCore.GetQueue(queueID),
			primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity), addOnReserving);
	}

	NIRCommandPoolInternal& CommandPoolQFGroupListInternal::GetCommandPoolWithoutIndividualReset(IDObject<VulkanSimplified::NIRPoolPointer> poolID)
	{
		return *_noIndividualResetCommandPoolList.GetObject(poolID);
	}

	IRCommandPoolInternal& CommandPoolQFGroupListInternal::GetCommandPoolWithIndividualReset(IDObject<VulkanSimplified::IRPoolPointer> poolID)
	{
		return *_individualResetCommandPoolList.GetObject(poolID);
	}

	const NIRCommandPoolInternal& CommandPoolQFGroupListInternal::GetCommandPoolWithoutIndividualReset(IDObject<VulkanSimplified::NIRPoolPointer> poolID) const
	{
		return *_noIndividualResetCommandPoolList.GetConstObject(poolID);
	}

	const IRCommandPoolInternal& CommandPoolQFGroupListInternal::GetCommandPoolWithIndividualReset(IDObject<VulkanSimplified::IRPoolPointer> poolID) const
	{
		return *_individualResetCommandPoolList.GetConstObject(poolID);
	}

	void CommandPoolQFGroupListInternal::SubmitBuffers(size_t queueID, const std::vector<VulkanSimplified::CommandBufferSubmissionData>& submissionData,
		std::optional<IDObject<AutoCleanupFence>> fenceID)
	{
		VkQueue queue = _deviceCore.GetQueue(queueID);
		std::uint32_t queueFamily = _deviceCore.GetQueuesFamily(queueID);

		if (_queueFamily != queueFamily)
			throw std::runtime_error("CommandPoolQFGroupListInternal::SubmitBuffers Error: Program tried to submit buffers to the wrong queue family!");

		if (submissionData.empty())
			throw std::runtime_error("CommandPoolQFGroupListInternal::SubmitBuffers Error: Program tried to submit no data!");

		std::vector<VkSubmitInfo> submitInfoList;
		std::vector<std::vector<VkSemaphore>> waitSemaphores;
		std::vector<std::vector<VkPipelineStageFlags>> pipelineStageFlags;
		std::vector<std::vector<VkCommandBuffer>> commandBuffers;
		std::vector<std::vector<VkSemaphore>> signalSemaphores;

		submitInfoList.reserve(submissionData.size());
		waitSemaphores.resize(submissionData.size());
		pipelineStageFlags.resize(submissionData.size());
		commandBuffers.resize(submissionData.size());
		signalSemaphores.resize(submissionData.size());

		for (size_t i = 0; i < submissionData.size(); ++i)
		{
			auto& submitInfo = submissionData[i];

			VkSubmitInfo add{};
			add.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

			if (submissionData[i].commandBufferIDs.empty())
				throw std::runtime_error("CommandPoolQFGroupListInternal::SubmitBuffers Error: Program tried to submit no commands buffer in a batch!");

			waitSemaphores[i].reserve(submitInfo.waitSemaphores.size());
			pipelineStageFlags[i].reserve(submitInfo.waitSemaphores.size());
			commandBuffers[i].reserve(submitInfo.commandBufferIDs.size());
			signalSemaphores[i].reserve(submitInfo.signalSemaphores.size());

			for (auto& waitSemaphoresData : submitInfo.waitSemaphores)
			{
				waitSemaphores[i].push_back(_synchronizationList.GetSemaphore(waitSemaphoresData.first));
				pipelineStageFlags[i].push_back(TranslateStageFlags(waitSemaphoresData.second));
			}

			add.waitSemaphoreCount = static_cast<std::uint32_t>(waitSemaphores[i].size());
			add.pWaitSemaphores = waitSemaphores[i].data();
			add.pWaitDstStageMask = pipelineStageFlags[i].data();

			for (auto& commandBufferID : submitInfo.commandBufferIDs)
			{
				commandBuffers[i].push_back(GetCommandBuffer(commandBufferID));
			}

			add.commandBufferCount = static_cast<std::uint32_t>(commandBuffers[i].size());
			add.pCommandBuffers = commandBuffers[i].data();

			for (auto& signalSemaphoresData : submitInfo.signalSemaphores)
			{
				signalSemaphores[i].push_back(_synchronizationList.GetSemaphore(signalSemaphoresData));
			}

			add.signalSemaphoreCount = static_cast<std::uint32_t>(signalSemaphores[i].size());
			add.pSignalSemaphores = signalSemaphores[i].data();

			submitInfoList.push_back(add);
		}

		VkFence fence = VK_NULL_HANDLE;
		if (fenceID.has_value())
			fence = _synchronizationList.GetFence(fenceID.value());

		if (vkQueueSubmit(queue, static_cast<std::uint32_t>(submitInfoList.size()), submitInfoList.data(), fence) != VK_SUCCESS)
			throw std::runtime_error("CommandPoolQFGroupListInternal::SubmitBuffers Error: Program failed to submit command buffers to queue!");
	}

	VkCommandBuffer CommandPoolQFGroupListInternal::GetCommandBuffer(VulkanSimplified::CommandBufferGenericID bufferID) const
	{
		VkCommandBuffer ret = VK_NULL_HANDLE;

		switch (bufferID.type)
		{
		case VulkanSimplified::CommandBufferIDType::NIR_PRIMARY:
			ret = GetCommandBuffer(bufferID.NIRPrimaryID.commandPoolID, bufferID.NIRPrimaryID.commandBufferID);
			break;
		case VulkanSimplified::CommandBufferIDType::NIR_SECONDARY:
			ret = GetCommandBuffer(bufferID.NIRSecondaryID.commandPoolID, bufferID.NIRSecondaryID.commandBufferID);
			break;
		case VulkanSimplified::CommandBufferIDType::IR_PRIMARY:
			ret = GetCommandBuffer(bufferID.IRPrimaryID.commandPoolID, bufferID.IRPrimaryID.commandBufferID);
			break;
		case VulkanSimplified::CommandBufferIDType::IR_SECONDARY:
			ret = GetCommandBuffer(bufferID.IRSecondaryID.commandPoolID, bufferID.IRSecondaryID.commandBufferID);
			break;
		case VulkanSimplified::CommandBufferIDType::UNKNOWN:
		default:
			throw std::runtime_error("CommandPoolQFGroupListInternal::GetCommandBuffer Error: Program was given an erroneous command buffer ID type!");
		}

		return ret;
	}

	VkCommandBuffer CommandPoolQFGroupListInternal::GetCommandBuffer(IDObject<VulkanSimplified::NIRPoolPointer> commandPoolID,
		IDObject<VulkanSimplified::PrimaryNIRPointer> commandBufferID) const
	{
		auto& commandPool = _noIndividualResetCommandPoolList.GetConstObject(commandPoolID);
		auto& commandBuffer = commandPool->GetPrimaryCommandBuffer(commandBufferID);

		return commandBuffer.GetCommandBuffer();
	}

	VkCommandBuffer CommandPoolQFGroupListInternal::GetCommandBuffer(IDObject<VulkanSimplified::NIRPoolPointer> commandPoolID,
		IDObject<VulkanSimplified::SecondaryNIRPointer> commandBufferID) const
	{
		auto& commandPool = _noIndividualResetCommandPoolList.GetConstObject(commandPoolID);
		auto& commandBuffer = commandPool->GetSecondaryCommandBuffer(commandBufferID);

		return commandBuffer.GetCommandBuffer();
	}

	VkCommandBuffer CommandPoolQFGroupListInternal::GetCommandBuffer(IDObject<VulkanSimplified::IRPoolPointer> commandPoolID,
		IDObject<VulkanSimplified::PrimaryIRPointer> commandBufferID) const
	{
		auto& commandPool = _individualResetCommandPoolList.GetConstObject(commandPoolID);
		auto& commandBuffer = commandPool->GetPrimaryCommandBuffer(commandBufferID);

		return commandBuffer.GetCommandBuffer();
	}

	VkCommandBuffer CommandPoolQFGroupListInternal::GetCommandBuffer(IDObject<VulkanSimplified::IRPoolPointer> commandPoolID,
		IDObject<VulkanSimplified::SecondaryIRPointer> commandBufferID) const
	{
		auto& commandPool = _individualResetCommandPoolList.GetConstObject(commandPoolID);
		auto& commandBuffer = commandPool->GetSecondaryCommandBuffer(commandBufferID);

		return commandBuffer.GetCommandBuffer();
	}

}