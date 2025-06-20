#pragma once

#include <CustomLists/IDObject.h>

#include "../../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../../Include/VSCommon/VSMemorySizeDef.h"

#include <vulkan/vulkan.hpp>
#include <optional>

namespace VulkanSimplified
{
	class AutoCleanupDataBuffer
	{
	public:
		VkBuffer GetDataBuffer() const;

		void BindDataBuffer(MemoryAllocationFullID allocationID, size_t bindingBeggining);

		std::optional<MemorySuballocationFullID> GetBoundMemorySuballocationData() const;

		uint32_t GetBuffersMemoryTypeMask() const;
		MemorySize GetBuffersSize() const;
		MemorySize GetBuffersRequiredAligment() const;

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
		std::optional<MemorySuballocationFullID> _memorySuballocation;

		void DestroyBuffer();
	};
}