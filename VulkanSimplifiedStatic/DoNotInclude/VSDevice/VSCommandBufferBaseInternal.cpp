#include "VSDeviceNIpch.h"
#include "VSCommandBufferBaseInternal.h"

#include <CustomLists/IDObject.h>

#include "VSPipelineDataListsInternal.h"
#include "VSSynchronizationDataListsInternal.h"
#include "VSWindowListInternal.h"
#include "VSWindowInternal.h"

namespace VulkanSimplifiedInternal
{
	CommandBufferBaseInternal::CommandBufferBaseInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		const ImageDataListsInternal& imageList, WindowListInternal& windowList, VkDevice device, VkCommandBuffer buffer, VkQueue queue) : _core(core),
		_deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData), _devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList),
		_imageList(imageList), _windowList(windowList), _device(device), _buffer(buffer), _queue(queue)
	{
	}

	CommandBufferBaseInternal::~CommandBufferBaseInternal()
	{
	}

	CommandBufferBaseInternal::CommandBufferBaseInternal(CommandBufferBaseInternal&& rhs) noexcept : _core(rhs._core), _deviceRenderPassData(rhs._deviceRenderPassData),
		_sharedRenderPassData(rhs._sharedRenderPassData), _devicePipelineData(rhs._devicePipelineData), _synchronizationList(rhs._synchronizationList), _imageList(rhs._imageList),
		_windowList(rhs._windowList), _device(rhs._device), _buffer(rhs._buffer), _queue(rhs._queue)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._buffer = VK_NULL_HANDLE;
		rhs._queue = VK_NULL_HANDLE;
	}

	VkCommandBuffer CommandBufferBaseInternal::GetCommandBuffer() const
	{
		return _buffer;
	}

	void CommandBufferBaseInternal::BeginRecording(VulkanSimplified::CommandBufferUsage usage)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		switch (usage)
		{
		case VulkanSimplified::CommandBufferUsage::MULTIPLE_USE_SIMULTANEOUS_USAGE:
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			break;
		case VulkanSimplified::CommandBufferUsage::MULTIPLE_USE_NO_SIMULTANEOUS_USAGE:
			break;
		case VulkanSimplified::CommandBufferUsage::ONE_USE:
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			break;
		default:
			throw std::runtime_error("CommandBufferBaseInternal::BeginRecording Error: Program was giwen an erroneous command buffer usage value!");
		}

		if (vkBeginCommandBuffer(_buffer, &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("CommandBufferBaseInternal::BeginRecording Error: Program failed to begin a command buffer's recording session!");
	}

	void CommandBufferBaseInternal::EndRecording()
	{
		if (vkEndCommandBuffer(_buffer) != VK_SUCCESS)
			throw std::runtime_error("CommandBufferBaseInternal::BeginRecording Error: Program failed to end a command buffer's recording session!");
	}

	void CommandBufferBaseInternal::BindGraphicsPipeline(IDObject<AutoCleanupGraphicsPipeline> pipelineID)
	{
		vkCmdBindPipeline(_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _devicePipelineData.GetGraphicsPipeline(pipelineID));
	}

	void CommandBufferBaseInternal::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		vkCmdDraw(_buffer, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	bool CommandBufferBaseInternal::AcquireNextImage(uint64_t timeout, std::optional<IDObject<AutoCleanupSemaphore>> semaphoreID, std::optional<IDObject<AutoCleanupFence>> fenceID,
		uint32_t& returnIndex, IDObject<VulkanSimplified::WindowPointer> windowID)
	{
		auto& window = _windowList.GetWindow(windowID);

		VkSemaphore semaphore = VK_NULL_HANDLE;
		VkFence fence = VK_NULL_HANDLE;

		if (semaphoreID.has_value())
			semaphore = _synchronizationList.GetSemaphore(semaphoreID.value());

		if (fenceID.has_value())
			fence = _synchronizationList.GetFence(fenceID.value());

		return window.AcquireNextImage(_device, timeout, semaphore, fence, returnIndex);
	}

}