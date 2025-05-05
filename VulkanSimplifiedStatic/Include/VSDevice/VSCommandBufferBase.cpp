#include "VSDeviceIpch.h"
#include "VSCommandBufferBase.h"

#include <CustomLists/IDObject.h>

#include "../../DoNotInclude/VSDevice/VSCommandBufferBaseInternal.h"

namespace VulkanSimplified
{
	CommandBufferBase::CommandBufferBase(VulkanSimplifiedInternal::CommandBufferBaseInternal& ref) : _internal(ref)
	{
	}

	CommandBufferBase::~CommandBufferBase()
	{
	}

	void CommandBufferBase::BeginRecording(CommandBufferUsage usage)
	{
		_internal.BeginRecording(usage);
	}

	void CommandBufferBase::EndRecording()
	{
		_internal.EndRecording();
	}

	void CommandBufferBase::BindGraphicsPipeline(IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> pipelineID)
	{
		_internal.BindGraphicsPipeline(pipelineID);
	}

	void CommandBufferBase::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		_internal.Draw(vertexCount, instanceCount, firstVertex, firstInstance);
	}

	bool CommandBufferBase::AcquireNextImage(uint64_t timeout, std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> semaphoreID,
		std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> fenceID, uint32_t& returnIndex, IDObject<WindowPointer> windowID)
	{
		return _internal.AcquireNextImage(timeout, semaphoreID, fenceID, returnIndex, windowID);
	}

}