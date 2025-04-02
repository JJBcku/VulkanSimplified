#pragma once

namespace VulkanSimplifiedInternal
{
	struct ShaderSpecializationElement
	{
		uint32_t ID;
		uint32_t offset;
		size_t size;

		ShaderSpecializationElement();

		bool operator==(const ShaderSpecializationElement& rhs) const noexcept = default;
		std::strong_ordering operator<=>(const ShaderSpecializationElement& rhs) const noexcept = default;
	};
}
