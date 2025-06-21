#include "VSDeviceNIpch.h"
#include "VSAutoCleanupDataBuffer.h"

namespace VulkanSimplified
{
	VkBuffer AutoCleanupDataBuffer::GetDataBuffer() const
	{
		return _buffer;
	}

	void AutoCleanupDataBuffer::BindDataBuffer(MemoryAllocationFullID allocationID, size_t bindingBeggining)
	{
		if (_memorySuballocation.has_value())
			throw std::runtime_error("AutoCleanupDataBuffer::BindDataBuffer Error: Program tried to bind an already bound data buffer!");

		_memorySuballocation.emplace(allocationID, bindingBeggining);
	}

	std::optional<MemorySuballocationFullID> AutoCleanupDataBuffer::GetBoundMemorySuballocationData() const
	{
		return _memorySuballocation;
	}

	uint32_t AutoCleanupDataBuffer::GetBuffersMemoryTypeMask() const
	{
		return _memReq.memoryTypeBits;
	}

	MemorySize AutoCleanupDataBuffer::GetBuffersSize() const
	{
		return _memReq.size;
	}

	MemorySize AutoCleanupDataBuffer::GetBuffersRequiredAligment() const
	{
		return _memReq.alignment;
	}

	AutoCleanupDataBuffer::AutoCleanupDataBuffer(VkDevice device, VkBuffer buffer) : _device(device), _buffer(buffer)
	{
		vkGetBufferMemoryRequirements(_device, _buffer, &_memReq);
	}

	AutoCleanupDataBuffer::~AutoCleanupDataBuffer()
	{
		DestroyBuffer();
	}

	AutoCleanupDataBuffer::AutoCleanupDataBuffer(AutoCleanupDataBuffer&& rhs) noexcept : _device(rhs._device), _buffer(rhs._buffer), _memReq(rhs._memReq),
		_memorySuballocation(std::move(rhs._memorySuballocation))
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._buffer = VK_NULL_HANDLE;
		rhs._memReq = {};
	}

	AutoCleanupDataBuffer& AutoCleanupDataBuffer::operator=(AutoCleanupDataBuffer&& rhs) noexcept
	{
		_device = rhs._device;
		_buffer = rhs._buffer;
		_memReq = rhs._memReq;
		_memorySuballocation = std::move(rhs._memorySuballocation);

		rhs._device = VK_NULL_HANDLE;
		rhs._buffer = VK_NULL_HANDLE;
		rhs._memReq = {};

		return *this;
	}

	void AutoCleanupDataBuffer::DestroyBuffer()
	{
		if (_buffer != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(_device, _buffer, nullptr);
			_buffer = VK_NULL_HANDLE;
		}
	}

}