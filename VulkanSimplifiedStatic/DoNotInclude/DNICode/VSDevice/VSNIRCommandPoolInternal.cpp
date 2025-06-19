#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSNIRCommandPoolInternal.h"

#include "../../DNIHeaders/VSDevice/VSPrimaryNIRCommandBufferInternal.h"
#include "../../DNIHeaders/VSDevice/VSSecondaryNIRCommandBufferInternal.h"

#include "../../DNIHeaders/VSDevice/VSSynchronizationDataListsInternal.h"
#include "../../DNIHeaders/VSDevice/VSWindowListInternal.h"
#include "../../DNIHeaders/VSDevice/VSWindowInternal.h"

namespace VulkanSimplifiedInternal
{
	NIRCommandPoolInternal::NIRCommandPoolInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device,
		VkCommandPool commandPool, VkQueue queue, size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity) : _core(core),
		_deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList),
		_imageList(imageList), _dataBufferList(dataBufferList), _windowList(windowList), _descriptorDataList(descriptorDataList), _device(device), _commandPool(commandPool),
		_queue(queue), _primaryBufferList(primaryBufferListInitialCapacity), _secondaryBufferList(secondaryBufferListInitialCapacity)
	{
	}

	NIRCommandPoolInternal::~NIRCommandPoolInternal()
	{
		if (_commandPool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(_device, _commandPool, nullptr);
		}
	}

	/*NIRCommandPoolInternal::NIRCommandPoolInternal(NIRCommandPoolInternal&& rhs) noexcept : _core(rhs._core), _deviceRenderPassData(rhs._deviceRenderPassData),
		_sharedRenderPassData(rhs._sharedRenderPassData), _devicePipelineData(rhs._devicePipelineData), _synchronizationList(rhs._synchronizationList), _imageList(rhs._imageList),
		_windowList(rhs._windowList), _device(rhs._device), _commandPool(rhs._commandPool), _queue(rhs._queue), _primaryBufferList(std::move(rhs._primaryBufferList)),
		_secondaryBufferList(std::move(rhs._secondaryBufferList))
	{
		_device = VK_NULL_HANDLE;
		_commandPool = VK_NULL_HANDLE;
		_queue = VK_NULL_HANDLE;
	}*/

	std::vector<IDObject<VulkanSimplified::PrimaryNIRPointer>> NIRCommandPoolInternal::AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		std::vector<IDObject<VulkanSimplified::PrimaryNIRPointer>> ret;

		if (buffersToAllocate == 0)
			throw std::runtime_error("NIRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program tried to allocate zero buffers!");

		ret.reserve(buffersToAllocate);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = _commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = buffersToAllocate;

		std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

		if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
			throw std::runtime_error("NIRCommandPoolInternal::AllocatePrimaryCommandBuffers Error: Program failed to allocate command buffers!");

		for (auto& buffer : add)
		{
			ret.push_back(_primaryBufferList.AddObject(std::make_unique<PrimaryNIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
				_synchronizationList, _imageList, _dataBufferList, _windowList, _descriptorDataList, _device, buffer, _queue), addOnReserving));
		}

		return ret;
	}

	std::vector<IDObject<VulkanSimplified::SecondaryNIRPointer>> NIRCommandPoolInternal::AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		std::vector<IDObject<VulkanSimplified::SecondaryNIRPointer>> ret;

		if (buffersToAllocate == 0)
			throw std::runtime_error("NIRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program tried to allocate zero buffers!");

		ret.reserve(buffersToAllocate);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = _commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		allocInfo.commandBufferCount = buffersToAllocate;

		std::vector<VkCommandBuffer> add(buffersToAllocate, VK_NULL_HANDLE);

		if (vkAllocateCommandBuffers(_device, &allocInfo, add.data()) != VK_SUCCESS)
			throw std::runtime_error("NIRCommandPoolInternal::AllocateSecondaryCommandBuffers Error: Program failed to allocate command buffers!");

		for (auto& buffer : add)
		{
			ret.push_back(_secondaryBufferList.AddObject(std::make_unique<SecondaryNIRCommandBufferInternal>(_core, _deviceRenderPassData, _sharedRenderPassData, _devicePipelineData,
				_synchronizationList, _imageList, _dataBufferList, _windowList, _descriptorDataList, _device, buffer, _queue), addOnReserving));
		}

		return ret;
	}

	PrimaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryNIRPointer> bufferID)
	{
		return *_primaryBufferList.GetObject(bufferID);
	}

	SecondaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryNIRPointer> bufferID)
	{
		return *_secondaryBufferList.GetObject(bufferID);
	}

	const PrimaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetPrimaryCommandBuffer(IDObject<VulkanSimplified::PrimaryNIRPointer> bufferID) const
	{
		return *_primaryBufferList.GetConstObject(bufferID);
	}

	const SecondaryNIRCommandBufferInternal& NIRCommandPoolInternal::GetSecondaryCommandBuffer(IDObject<VulkanSimplified::SecondaryNIRPointer> bufferID) const
	{
		return *_secondaryBufferList.GetConstObject(bufferID);
	}

	void NIRCommandPoolInternal::ResetCommandPool(bool freeResources)
	{
		VkCommandPoolResetFlags flags = 0;
		if (freeResources)
			flags = VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT;

		vkResetCommandPool(_device, _commandPool, flags);
	}

	bool NIRCommandPoolInternal::PresentSwapchainToQueue(IDObject<VulkanSimplified::WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs,
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
		presentInfo.waitSemaphoreCount = static_cast<uint32_t>(semaphores.size());
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