#include "VSDeviceNIpch.h"
#include "VSCommandBufferBaseInternal.h"

#include <CustomLists/IDObject.h>

#include "VSDeviceCoreInternal.h"
#include "VSPipelineDataListsInternal.h"
#include "VSDataBufferListsInternal.h"
#include "VSImageDataListsInternal.h"
#include "VSSynchronizationDataListsInternal.h"
#include "VSWindowListInternal.h"
#include "VSWindowInternal.h"
#include "VSDescriptorDataListsInternal.h"

#include "../../Include/VSDevice/VSDataBuffersCopyRegionData.h"
#include "../../Include/VSDevice/VSGlobalMemoryBarrierData.h"
#include "../../Include/VSDevice/VSDataBuffersMemoryBarrierData.h"
#include "../../Include/VSDevice/VSImagesMemoryBarrierData.h"
#include "../../Include/VSDevice/VSQueueOwnershipTransferData.h"
#include "../../Include/VSDevice/VSIndexType.h"

#include "../../Include/VSDevice/VSDescriptorPoolGenericID.h"

#include "../VSCommon/VSPipelineStageFlagsInternal.h"
#include "../VSCommon/VSAccessFlagsInternal.h"
#include "../VSCommon/VSImageLayoutFlagsInternal.h"

#include "VSAutoCleanupColorRenderTargetImage.h"
#include "VSAutoCleanup2DTexture.h"

#include "VSAutoCleanupStagingBuffer.h"

namespace VulkanSimplifiedInternal
{
	CommandBufferBaseInternal::CommandBufferBaseInternal(const DeviceCoreInternal& core, const RenderPassListInternal& deviceRenderPassData,
		const SharedRenderPassDataListInternal& sharedRenderPassData, const PipelineDataListsInternal& devicePipelineData, const SynchronizationDataListsInternal& synchronizationList,
		ImageDataListsInternal& imageList, DataBufferListsInternal& dataBufferList, WindowListInternal& windowList, DescriptorDataListsInternal& descriptorDataList, VkDevice device,
		VkCommandBuffer buffer, VkQueue queue) : _core(core), _deviceRenderPassData(deviceRenderPassData), _sharedRenderPassData(sharedRenderPassData),
		_devicePipelineData(devicePipelineData), _synchronizationList(synchronizationList), _imageList(imageList), _dataBufferList(dataBufferList), _windowList(windowList),
		_descriptorDataList(descriptorDataList), _device(device), _buffer(buffer), _queue(queue)
	{
	}

	CommandBufferBaseInternal::~CommandBufferBaseInternal()
	{
	}

	CommandBufferBaseInternal::CommandBufferBaseInternal(CommandBufferBaseInternal&& rhs) noexcept : _core(rhs._core), _deviceRenderPassData(rhs._deviceRenderPassData),
		_sharedRenderPassData(rhs._sharedRenderPassData), _devicePipelineData(rhs._devicePipelineData), _synchronizationList(rhs._synchronizationList), _imageList(rhs._imageList),
		_dataBufferList(rhs._dataBufferList), _windowList(rhs._windowList), _descriptorDataList(rhs._descriptorDataList), _device(rhs._device), _buffer(rhs._buffer), _queue(rhs._queue)
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

	void CommandBufferBaseInternal::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t firstVertexOffset, uint32_t firstInstance)
	{
		vkCmdDrawIndexed(_buffer, indexCount, instanceCount, firstIndex, firstVertexOffset, firstInstance);
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

	void CommandBufferBaseInternal::TransferDataToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupVertexBuffer> dstBufferID,
		const VulkanSimplified::DataBuffersCopyRegionData& copyRegion)
	{
		auto stagingBufferSize = _dataBufferList.GetStagingBuffersSize(srcBufferID);
		auto stagingBuffer = _dataBufferList.GetStagingBuffer(srcBufferID);

		if (copyRegion.srcOffset >= stagingBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToVertexBuffer Error: Program tried to read past the end of the staging buffer!");

		if (copyRegion.writeSize > stagingBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToVertexBuffer Error: Program tried to read more data the there is in the entire staging buffer!");

		if (copyRegion.writeSize > stagingBufferSize - copyRegion.srcOffset)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToVertexBuffer Error: Program tried to read more data the there is past the staging buffer's offset!");

		auto dstBufferSize = _dataBufferList.GetVertexBuffersSize(dstBufferID);
		auto dstBuffer = _dataBufferList.GetVertexBuffer(dstBufferID);

		if (copyRegion.dstOffset >= dstBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToVertexBuffer Error: Program tried to write past the end of the vertex buffer!");

		if (copyRegion.writeSize > dstBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToVertexBuffer Error: Program tried to write more data the there is in the entire vertex buffer!");

		if (copyRegion.writeSize > dstBufferSize - copyRegion.dstOffset)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToVertexBuffer Error: Program tried to write more data the there is past the vertex buffer's offset!");

		VkBufferCopy copy{};
		copy.srcOffset = copyRegion.srcOffset;
		copy.dstOffset = copyRegion.dstOffset;
		copy.size = copyRegion.writeSize;

		vkCmdCopyBuffer(_buffer, stagingBuffer, dstBuffer, 1, &copy);
	}

	void CommandBufferBaseInternal::TransferDataListToVertexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupVertexBuffer> dstBufferID,
		const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList)
	{
		if (copyRegionsList.empty())
			return;

		if (copyRegionsList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Copy regions list overflowed!");

		std::vector<VkBufferCopy> copyRegionsData;
		copyRegionsData.reserve(copyRegionsList.size());

		auto stagingBufferSize = _dataBufferList.GetStagingBuffersSize(srcBufferID);
		auto stagingBuffer = _dataBufferList.GetStagingBuffer(srcBufferID);

		auto dstBufferSize = _dataBufferList.GetVertexBuffersSize(dstBufferID);
		auto dstBuffer = _dataBufferList.GetVertexBuffer(dstBufferID);

		for (size_t i = 0; i < copyRegionsList.size(); ++i)
		{
			auto& copyRegion = copyRegionsList[i];

			if (copyRegion.srcOffset >= stagingBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Program tried to read past the end of the staging buffer!");

			if (copyRegion.writeSize > stagingBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Program tried to read more data the there is in the entire staging buffer!");

			if (copyRegion.writeSize > stagingBufferSize - copyRegion.srcOffset)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Program tried to read more data the there is past the staging buffer's offset!");

			if (copyRegion.dstOffset >= dstBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Program tried to write past the end of the vertex buffer!");

			if (copyRegion.writeSize > dstBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Program tried to write more data the there is in the entire vertex buffer!");

			if (copyRegion.writeSize > dstBufferSize - copyRegion.dstOffset)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToVertexBuffer Error: Program tried to write more data the there is past the vertex buffer's offset!");

			VkBufferCopy copy{};
			copy.srcOffset = copyRegion.srcOffset;
			copy.dstOffset = copyRegion.dstOffset;
			copy.size = copyRegion.writeSize;

			copyRegionsData.push_back(copy);
		}

		vkCmdCopyBuffer(_buffer, stagingBuffer, dstBuffer, static_cast<uint32_t>(copyRegionsData.size()), copyRegionsData.data());
	}

	void CommandBufferBaseInternal::TransferDataToIndexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupIndexBuffer> dstBufferID, const VulkanSimplified::DataBuffersCopyRegionData& copyRegion)
	{
		auto stagingBufferSize = _dataBufferList.GetStagingBuffersSize(srcBufferID);
		auto stagingBuffer = _dataBufferList.GetStagingBuffer(srcBufferID);

		if (copyRegion.srcOffset >= stagingBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToIndexBuffer Error: Program tried to read past the end of the staging buffer!");

		if (copyRegion.writeSize > stagingBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToIndexBuffer Error: Program tried to read more data the there is in the entire staging buffer!");

		if (copyRegion.writeSize > stagingBufferSize - copyRegion.srcOffset)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToIndexBuffer Error: Program tried to read more data the there is past the staging buffer's offset!");

		auto dstBufferSize = _dataBufferList.GetIndexBuffersSize(dstBufferID);
		auto dstBuffer = _dataBufferList.GetIndexBuffer(dstBufferID);

		if (copyRegion.dstOffset >= dstBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToIndexBuffer Error: Program tried to write past the end of the index buffer!");

		if (copyRegion.writeSize > dstBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToIndexBuffer Error: Program tried to write more data the there is in the entire index buffer!");

		if (copyRegion.writeSize > dstBufferSize - copyRegion.dstOffset)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToIndexBuffer Error: Program tried to write more data the there is past the index buffer's offset!");

		VkBufferCopy copy{};
		copy.srcOffset = copyRegion.srcOffset;
		copy.dstOffset = copyRegion.dstOffset;
		copy.size = copyRegion.writeSize;

		vkCmdCopyBuffer(_buffer, stagingBuffer, dstBuffer, 1, &copy);
	}

	void CommandBufferBaseInternal::TransferDataListToIndexBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupIndexBuffer> dstBufferID, const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList)
	{
		if (copyRegionsList.empty())
			return;

		if (copyRegionsList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Copy regions list overflowed!");

		std::vector<VkBufferCopy> copyRegionsData;
		copyRegionsData.reserve(copyRegionsList.size());

		auto stagingBufferSize = _dataBufferList.GetStagingBuffersSize(srcBufferID);
		auto stagingBuffer = _dataBufferList.GetStagingBuffer(srcBufferID);

		auto dstBufferSize = _dataBufferList.GetIndexBuffersSize(dstBufferID);
		auto dstBuffer = _dataBufferList.GetIndexBuffer(dstBufferID);

		for (size_t i = 0; i < copyRegionsList.size(); ++i)
		{
			auto& copyRegion = copyRegionsList[i];

			if (copyRegion.srcOffset >= stagingBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Program tried to read past the end of the staging buffer!");

			if (copyRegion.writeSize > stagingBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Program tried to read more data the there is in the entire staging buffer!");

			if (copyRegion.writeSize > stagingBufferSize - copyRegion.srcOffset)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Program tried to read more data the there is past the staging buffer's offset!");

			if (copyRegion.dstOffset >= dstBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Program tried to write past the end of the index buffer!");

			if (copyRegion.writeSize > dstBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Program tried to write more data the there is in the entire index buffer!");

			if (copyRegion.writeSize > dstBufferSize - copyRegion.dstOffset)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToIndexBuffer Error: Program tried to write more data the there is past the index buffer's offset!");

			VkBufferCopy copy{};
			copy.srcOffset = copyRegion.srcOffset;
			copy.dstOffset = copyRegion.dstOffset;
			copy.size = copyRegion.writeSize;

			copyRegionsData.push_back(copy);
		}

		vkCmdCopyBuffer(_buffer, stagingBuffer, dstBuffer, static_cast<uint32_t>(copyRegionsData.size()), copyRegionsData.data());
	}

	void CommandBufferBaseInternal::TransferDataToUniformBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupUniformBuffer> dstBufferID,
		const VulkanSimplified::DataBuffersCopyRegionData& copyRegion)
	{
		auto stagingBufferSize = _dataBufferList.GetStagingBuffersSize(srcBufferID);
		auto stagingBuffer = _dataBufferList.GetStagingBuffer(srcBufferID);

		if (copyRegion.srcOffset >= stagingBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToUniformBuffer Error: Program tried to read past the end of the staging buffer!");

		if (copyRegion.writeSize > stagingBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToUniformBuffer Error: Program tried to read more data the there is in the entire staging buffer!");

		if (copyRegion.writeSize > stagingBufferSize - copyRegion.srcOffset)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToUniformBuffer Error: Program tried to read more data the there is past the staging buffer's offset!");

		auto dstBufferSize = _dataBufferList.GetUniformBuffersSize(dstBufferID);
		auto dstBuffer = _dataBufferList.GetUniformBuffer(dstBufferID);

		if (copyRegion.dstOffset >= dstBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToUniformBuffer Error: Program tried to write past the end of the uniform buffer!");

		if (copyRegion.writeSize > dstBufferSize)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToUniformBuffer Error: Program tried to write more data the there is in the entire uniform buffer!");

		if (copyRegion.writeSize > dstBufferSize - copyRegion.dstOffset)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataToUniformBuffer Error: Program tried to write more data the there is past the uniform buffer's offset!");

		VkBufferCopy copy{};
		copy.srcOffset = copyRegion.srcOffset;
		copy.dstOffset = copyRegion.dstOffset;
		copy.size = copyRegion.writeSize;

		vkCmdCopyBuffer(_buffer, stagingBuffer, dstBuffer, 1, &copy);
	}

	void CommandBufferBaseInternal::TransferDataListToUniformBuffer(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanupUniformBuffer> dstBufferID, const std::vector<VulkanSimplified::DataBuffersCopyRegionData>& copyRegionsList)
	{
		if (copyRegionsList.empty())
			return;

		if (copyRegionsList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Copy regions list overflowed!");

		std::vector<VkBufferCopy> copyRegionsData;
		copyRegionsData.reserve(copyRegionsList.size());

		auto stagingBufferSize = _dataBufferList.GetStagingBuffersSize(srcBufferID);
		auto stagingBuffer = _dataBufferList.GetStagingBuffer(srcBufferID);

		auto dstBufferSize = _dataBufferList.GetUniformBuffersSize(dstBufferID);
		auto dstBuffer = _dataBufferList.GetUniformBuffer(dstBufferID);

		for (size_t i = 0; i < copyRegionsList.size(); ++i)
		{
			auto& copyRegion = copyRegionsList[i];

			if (copyRegion.srcOffset >= stagingBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Program tried to read past the end of the staging buffer!");

			if (copyRegion.writeSize > stagingBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Program tried to read more data the there is in the entire staging buffer!");

			if (copyRegion.writeSize > stagingBufferSize - copyRegion.srcOffset)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Program tried to read more data the there is past the staging buffer's offset!");

			if (copyRegion.dstOffset >= dstBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Program tried to write past the end of the uniform buffer!");

			if (copyRegion.writeSize > dstBufferSize)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Program tried to write more data the there is in the entire uniform buffer!");

			if (copyRegion.writeSize > dstBufferSize - copyRegion.dstOffset)
				throw std::runtime_error("CommandBufferBaseInternal::TransferDataListToUniformBuffer Error: Program tried to write more data the there is past the uniform buffer's offset!");

			VkBufferCopy copy{};
			copy.srcOffset = copyRegion.srcOffset;
			copy.dstOffset = copyRegion.dstOffset;
			copy.size = copyRegion.writeSize;

			copyRegionsData.push_back(copy);
		}

		vkCmdCopyBuffer(_buffer, stagingBuffer, dstBuffer, static_cast<uint32_t>(copyRegionsData.size()), copyRegionsData.data());
	}

	void CommandBufferBaseInternal::TransferDataTo2dTextureSimple(IDObject<AutoCleanupStagingBuffer> srcBufferID, IDObject<AutoCleanup2DTexture> dstTextureID, uint32_t mipLevel)
	{
		auto& bufferData = _dataBufferList.GetStagingBufferInternal(srcBufferID);

		auto& imageData = _imageList.Get2DTextureImageInternal(dstTextureID);

		VkBuffer buffer = bufferData.GetDataBuffer();

		VkImage image = imageData.GetImage();
		VkImageLayout layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

		if (imageData.GetMipmapLevels() <= mipLevel)
			throw std::runtime_error("CommandBufferBaseInternal::TransferDataTo2dTextureSimple Error: Program was give an erroneous mipmap level value!");

		VkBufferImageCopy bufferCopy{};
		bufferCopy.bufferOffset = 0;
		bufferCopy.bufferRowLength = 0;
		bufferCopy.bufferImageHeight = 0;

		bufferCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		bufferCopy.imageSubresource.baseArrayLayer = 0;
		bufferCopy.imageSubresource.layerCount = 1;
		bufferCopy.imageSubresource.mipLevel = mipLevel;

		bufferCopy.imageOffset.x = 0;
		bufferCopy.imageOffset.y = 0;
		bufferCopy.imageOffset.z = 0;

		bufferCopy.imageExtent.width = std::max(1U, imageData.GetWidth() >> mipLevel);
		bufferCopy.imageExtent.height = std::max(1U, imageData.GetHeight() >> mipLevel);
		bufferCopy.imageExtent.depth = 1;

		vkCmdCopyBufferToImage(_buffer, buffer, image, layout, 1, &bufferCopy);
	}

	void CommandBufferBaseInternal::CreatePipelineBarrier(VulkanSimplified::PipelineStageFlags srcStages, VulkanSimplified::PipelineStageFlags dstStages,
		const std::vector<VulkanSimplified::GlobalMemoryBarrierData>& globalMemoryBarrierData,
		const std::vector<VulkanSimplified::DataBuffersMemoryBarrierData>& dataBuffersBarrierData, const std::vector<VulkanSimplified::ImagesMemoryBarrierData>& imageBarrierData)
	{
		if (globalMemoryBarrierData.empty() && dataBuffersBarrierData.empty() && imageBarrierData.empty())
			return;

		if (globalMemoryBarrierData.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::CreatePipelineBarrier Error: Global memory barrier list overflowed!");

		if (dataBuffersBarrierData.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::CreatePipelineBarrier Error: Data buffer memory barrier list overflowed!");

		if (imageBarrierData.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::CreatePipelineBarrier Error: Image memory barrier list overflowed!");

		VkPipelineStageFlags srcStagesFlags = TranslateStageFlags(srcStages);
		VkPipelineStageFlags dstStagesFlags = TranslateStageFlags(dstStages);

		std::vector<VkMemoryBarrier> globalMemoryBarriersDataList;
		std::vector<VkBufferMemoryBarrier> dataBuffersMemoryBarriersDataList;
		std::vector<VkImageMemoryBarrier> imagesMemoryBarriersDataList;

		globalMemoryBarriersDataList.resize(globalMemoryBarrierData.size());
		dataBuffersMemoryBarriersDataList.resize(dataBuffersBarrierData.size());
		imagesMemoryBarriersDataList.resize(imageBarrierData.size());

		for (size_t i = 0; i < globalMemoryBarrierData.size(); ++i)
		{
			auto& inData = globalMemoryBarrierData[i];
			auto& outData = globalMemoryBarriersDataList[i];

			outData.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;

			outData.srcAccessMask = TranslataAccessFlags(inData.srcAccess);
			outData.dstAccessMask = TranslataAccessFlags(inData.dstAccess);
		}

		for (size_t i = 0; i < dataBuffersBarrierData.size(); ++i)
		{
			auto& inData = dataBuffersBarrierData[i];
			auto& outData = dataBuffersMemoryBarriersDataList[i];

			outData.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;

			outData.srcAccessMask = TranslataAccessFlags(inData.srcAccess);
			outData.dstAccessMask = TranslataAccessFlags(inData.dstAccess);

			if (inData.queueData.has_value())
			{
				outData.srcQueueFamilyIndex = _core.GetQueuesFamily(inData.queueData.value().srcQueueIndex);
				outData.dstQueueFamilyIndex = _core.GetQueuesFamily(inData.queueData.value().dstQueueIndex);
			}
			else
			{
				outData.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				outData.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			}

			switch (inData.bufferID.type)
			{
			case VulkanSimplified::DataBuffersIDType::VERTEX:
				outData.buffer = _dataBufferList.GetVertexBuffer(inData.bufferID.vertexID.ID);
				break;
			case VulkanSimplified::DataBuffersIDType::STAGING:
				outData.buffer = _dataBufferList.GetStagingBuffer(inData.bufferID.stagingID.ID);
				break;
			case VulkanSimplified::DataBuffersIDType::INDEX:
				outData.buffer = _dataBufferList.GetIndexBuffer(inData.bufferID.indexID.ID);
				break;
			case VulkanSimplified::DataBuffersIDType::UNIFORM:
				outData.buffer = _dataBufferList.GetUniformBuffer(inData.bufferID.uniformID.ID);
				break;
			case VulkanSimplified::DataBuffersIDType::UNKNOWN:
			default:
				throw std::runtime_error("CommandBufferBaseInternal::CreatePipelineBarrier Error: Program was given an erroneous generic data buffer id type!");
			}

			outData.offset = 0;
			outData.size = VK_WHOLE_SIZE;
		}

		for (size_t i = 0; i < imageBarrierData.size(); ++i)
		{
			auto& inData = imageBarrierData[i];
			auto& outData = imagesMemoryBarriersDataList[i];

			outData.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;

			outData.srcAccessMask = TranslataAccessFlags(inData.srcAccess);
			outData.dstAccessMask = TranslataAccessFlags(inData.dstAccess);

			outData.oldLayout = TranslateImageLayout(inData.oldLayout);
			outData.newLayout = TranslateImageLayout(inData.newLayout);

			if (inData.queueData.has_value())
			{
				outData.srcQueueFamilyIndex = _core.GetQueuesFamily(inData.queueData.value().srcQueueIndex);
				outData.dstQueueFamilyIndex = _core.GetQueuesFamily(inData.queueData.value().dstQueueIndex);
			}
			else
			{
				outData.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				outData.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			}

			const AutoCleanupImage* imagePtr = nullptr;

			switch (inData.imageID.type)
			{
			case VulkanSimplified::ImagesIDType::COLOR_RENDER_TARGET:
				imagePtr = &_imageList.GetColorRenderTargetImageInternal(inData.imageID.colorRenderTargetID.ID);
				outData.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				outData.subresourceRange.baseArrayLayer = 0;
				outData.subresourceRange.baseMipLevel = 0;
				outData.subresourceRange.layerCount = 1;
				outData.subresourceRange.levelCount = 1;
				break;
			case VulkanSimplified::ImagesIDType::TEXTURE_2D:
				imagePtr = &_imageList.Get2DTextureImageInternal(inData.imageID.texture2DID.ID);
				outData.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				outData.subresourceRange.baseArrayLayer = 0;
				outData.subresourceRange.baseMipLevel = 0;
				outData.subresourceRange.layerCount = 1;
				outData.subresourceRange.levelCount = imagePtr->GetMipmapLevels();
				break;
			case VulkanSimplified::ImagesIDType::UNKNOWN:
			default:
				throw std::runtime_error("CommandBufferBaseInternal::CreatePipelineBarrier Error: Program was given an erroneous generic image id type!");
			}

			outData.image = imagePtr->GetImage();
		}

		vkCmdPipelineBarrier(_buffer, srcStagesFlags, dstStagesFlags, 0, static_cast<uint32_t>(globalMemoryBarriersDataList.size()), globalMemoryBarriersDataList.data(),
			static_cast<uint32_t>(dataBuffersMemoryBarriersDataList.size()), dataBuffersMemoryBarriersDataList.data(), static_cast<uint32_t>(imagesMemoryBarriersDataList.size()),
			imagesMemoryBarriersDataList.data());
	}

	void CommandBufferBaseInternal::BindVertexBuffers(uint32_t firstBinding,
		const std::vector<std::pair<IDObject<AutoCleanupVertexBuffer>, VulkanSimplified::MemorySize>>& buffersDataList)
	{
		if (buffersDataList.empty())
			return;

		if (buffersDataList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::BindVertexBuffers Error: buffer data list overflowed!");

		std::vector<VkBuffer> buffers;
		std::vector<VkDeviceSize> offsets;

		buffers.resize(buffersDataList.size(), VK_NULL_HANDLE);
		offsets.resize(buffersDataList.size(), 0);

		for (size_t i = 0; i < buffersDataList.size(); ++i)
		{
			buffers[i] = _dataBufferList.GetVertexBuffer(buffersDataList[i].first);
			offsets[i] = buffersDataList[i].second;
		}

		vkCmdBindVertexBuffers(_buffer, firstBinding, static_cast<uint32_t>(buffers.size()), buffers.data(), offsets.data());
	}

	void CommandBufferBaseInternal::BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, VulkanSimplified::MemorySize buffersOffset, VulkanSimplified::IndexType indexType)
	{
		auto buffer = _dataBufferList.GetIndexBuffer(bufferID);

		VkIndexType type = VK_INDEX_TYPE_MAX_ENUM;

		switch (indexType)
		{
		case VulkanSimplified::IndexType::INDEX_TYPE_16_BITS:
			type = VK_INDEX_TYPE_UINT16;
			break;
		case VulkanSimplified::IndexType::INDEX_TYPE_32_BITS:
			type = VK_INDEX_TYPE_UINT32;
			break;
		default:
			throw std::runtime_error("CommandBufferBaseInternal::BindIndexBuffer Error: Program was given an erroneous index type value!");
		}

		vkCmdBindIndexBuffer(_buffer, buffer, buffersOffset, type);
	}

	void CommandBufferBaseInternal::BindDescriptorSetsToGraphicsPipeline(IDObject<AutoCleanupPipelineLayout> pipelineLayoutID, uint32_t firstSet,
		VulkanSimplified::DescriptorPoolGenericID descriptorPoolID, const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDList,
		const std::vector<uint32_t>& dynamicOffsetList)
	{
		if (descriptorSetIDList.empty())
			return;

		if (descriptorSetIDList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::BindDescriptorSetsToGraphicsPipeline Error: Descriptor set id list overflowed!");

		if (dynamicOffsetList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("CommandBufferBaseInternal::BindDescriptorSetsToGraphicsPipeline Error: Dynamic offsets list overflowed!");

		VkPipelineLayout layout = _devicePipelineData.GetPipelineLayout(pipelineLayoutID);

		std::vector<VkDescriptorSet> descriptorSetList;

		if (descriptorPoolID.type == VulkanSimplified::DescriptorPoolIDType::NIF)
		{
			descriptorSetList = _descriptorDataList.GetNIFDescriptorSetList(descriptorPoolID.NifID.ID, descriptorSetIDList);
		}
		else if (descriptorPoolID.type == VulkanSimplified::DescriptorPoolIDType::IF)
		{
			descriptorSetList = _descriptorDataList.GetIFDescriptorSetList(descriptorPoolID.IfID.ID, descriptorSetIDList);
		}
		else
			throw std::runtime_error("CommandBufferBaseInternal::BindDescriptorSetsToGraphicsPipeline Error: Program was given an erroneous descriptor pool ID!");

		vkCmdBindDescriptorSets(_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, firstSet, static_cast<uint32_t>(descriptorSetList.size()),
			descriptorSetList.data(), static_cast<uint32_t>(dynamicOffsetList.size()), dynamicOffsetList.data());
	}

}