#include "VSDeviceNIpch.h"
#include "VSIRCommandPoolInternal.h"

#include "VSSynchronizationDataListsInternal.h"
#include "VSWindowListInternal.h"
#include "VSWindowInternal.h"

#include "VSPrimaryIRCommandBufferInternal.h"
#include "VSSecondaryIRCommandBufferInternal.h"

namespace VulkanSimplifiedInternal
{
	IRCommandPoolInternal::IRCommandPoolInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		const ImageDataListsInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandPool commandPool, VkQueue queue,
		size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity) : _core(core), _deviceRenderPassData(deviceRenderPassData),
		_sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList), _windowList(windowList),
		_device(device), _commandPool(commandPool), _queue(queue), _primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
	{
	}

	IRCommandPoolInternal::~IRCommandPoolInternal()
	{
		if (_commandPool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(_device, _commandPool, nullptr);
		}
	}

	std::vector<IDObject<VulkanSimplified::PrimaryIRPointer>> IRCommandPoolInternal::AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		std::vector<IDObject<VulkanSimplified::PrimaryIRPointer>> ret;

		if (buffersToAllocate == 0)
			throw std::runtime_error("IRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program tried to allocate zero buffers!");

		ret.reserve(buffersToAllocate);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = _commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = buffersToAllocate;

		std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

		if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
			throw std::runtime_error("IRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program failed to allocate command buffers!");

		for (auto& buffer : add)
		{
			ret.push_back(_primaryBufferList.AddObject(std::make_unique<PrimaryIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
				_synchronizationList, _imageList, _windowList, _device, buffer, _queue), addOnReserving));
		}

		return ret;
	}

	std::vector<IDObject<VulkanSimplified::SecondaryIRPointer>> IRCommandPoolInternal::AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		std::vector<IDObject<VulkanSimplified::SecondaryIRPointer>> ret;

		if (buffersToAllocate == 0)
			throw std::runtime_error("IRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program tried to allocate zero buffers!");

		ret.reserve(buffersToAllocate);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = _commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		allocInfo.commandBufferCount = buffersToAllocate;

		std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

		if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
			throw std::runtime_error("IRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program failed to allocate command buffers!");

		for (auto& buffer : add)
		{
			ret.push_back(_secondaryBufferList.AddObject(std::make_unique<SecondaryIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
				_synchronizationList, _imageList, _windowList, _device, buffer, _queue), addOnReserving));
		}

		return ret;
	}

	PrimaryIRCommandBufferInternal& IRCommandPoolInternal::GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryIRPointer> bufferID)
	{
		return *_primaryBufferList.GetObject(bufferID);
	}

	SecondaryIRCommandBufferInternal& IRCommandPoolInternal::GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryIRPointer> bufferID)
	{
		return *_secondaryBufferList.GetObject(bufferID);
	}

	const PrimaryIRCommandBufferInternal& IRCommandPoolInternal::GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryIRPointer> bufferID) const
	{
		return *_primaryBufferList.GetConstObject(bufferID);
	}

	const SecondaryIRCommandBufferInternal& IRCommandPoolInternal::GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryIRPointer> bufferID) const
	{
		return *_secondaryBufferList.GetConstObject(bufferID);
	}

	void IRCommandPoolInternal::ResetCommandPool(bool freeResources)
	{
		VkCommandPoolResetFlags flags = 0;
		if (freeResources)
			flags = VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT;

		vkResetCommandPool(_device, _commandPool, flags);
	}

	bool IRCommandPoolInternal::PresentSwapchainToQueue(IDObject<VulkanSimplified::WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs,
		uint32_t imageIndex)
	{
		auto& window = _windowList.GetWindow(windowID);

		std::vector<VkSemaphore> semaphores;
		semaphores.reserve(waitSemaphoreIDs.size());

		for (auto& semaphore : waitSemaphoreIDs)
			semaphores.push_back(_synchronizationList.GetSemaphore(semaphore));

		VkSwapchainKHR swapchain = window.GetSwapchain();

		if (swapchain == VK_NULL_HANDLE)
			throw std::runtime_error("NIRCommandPoolInternal::PresentSwapchainToQueue Error: Program tried to present image from a non-existent swapchain!");

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = static_cast<std::uint32_t>(semaphores.size());
		presentInfo.pWaitSemaphores = semaphores.data();
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain;
		presentInfo.pImageIndices = &imageIndex;

		VkResult result = vkQueuePresentKHR(_queue, &presentInfo);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("NIRCommandPoolInternal::PresentSwapchainToQueue Error: Program failed to present a swapchain image to queue!");

		return result == VK_SUCCESS;
	}

}