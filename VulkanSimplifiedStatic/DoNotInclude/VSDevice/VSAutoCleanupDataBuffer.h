#pragma once

#include <CustomLists/IDObject.h>

#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../Include/VSCommon/VSMemorySizeDef.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupDataBuffer
	{
	public:
		VkBuffer GetDataBuffer() const;

		void BindDataBuffer(VulkanSimplified::MemoryAllocationFullID allocationID, size_t bindingBeggining);

		std::optional<VulkanSimplified::MemorySuballocationFullID> GetBoundMemorySuballocationData() const;

		uint32_t GetBuffersMemoryTypeMask() const;
		VulkanSimplified::MemorySize GetBuffersSize() const;
		VulkanSimplified::MemorySize GetBuffersRequiredAligment() const;

	protected:
		AutoCleanupDataBuffer(VkDevice device, VkBuffer buffer);
		~AutoCleanupDataBuffer();

		AutoCleanupDataBuffer(const AutoCleanupDataBuffer& rhs) noexcept = delete;
		AutoCleanupDataBuffer(AutoCleanupDataBuffer&& rhs) noexcept;

		AutoCleanupDataBuffer& operator=(const AutoCleanupDataBuffer& rhs) noexcept = delete;
		AutoCleanupDataBuffer& operator=(AutoCleanupDataBuffer&& rhs) noexcept;

	private:
		VkDevice _device;
		VkBuffer _buffer;

		VkMemoryRequirements _memReq;
		std::optional<VulkanSimplified::MemorySuballocationFullID> _memorySuballocation;

		void DestroyBuffer();
	};
}