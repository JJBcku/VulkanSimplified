#pragma once

#include <compare>
#include <stdint.h>

namespace VulkanSimplifiedInternal
{
	struct RenderPassDoubleColorClearValues
	{
		double r;
		double g;
		double b;
		double a;

		RenderPassDoubleColorClearValues() = default;

		bool operator==(const RenderPassDoubleColorClearValues&) const noexcept = default;
		std::partial_ordering operator<=>(const RenderPassDoubleColorClearValues&) const noexcept = default;
	};

	struct RenderPassInt64ColorClearValues
	{
		int64_t r;
		int64_t g;
		int64_t b;
		int64_t a;

		RenderPassInt64ColorClearValues() = default;

		bool operator==(const RenderPassInt64ColorClearValues&) const noexcept = default;
		std::strong_ordering operator<=>(const RenderPassInt64ColorClearValues&) const noexcept = default;
	};

	struct RenderPassUInt64ColorClearValues
	{
		uint64_t r;
		uint64_t g;
		uint64_t b;
		uint64_t a;

		RenderPassUInt64ColorClearValues() = default;

		bool operator==(const RenderPassUInt64ColorClearValues&) const noexcept = default;
		std::strong_ordering operator<=>(const RenderPassUInt64ColorClearValues&) const noexcept = default;
	};

	struct RenderPassFloatColorClearValues
	{
		float r;
		float g;
		float b;
		float a;

		RenderPassFloatColorClearValues() = default;

		bool operator==(const RenderPassFloatColorClearValues&) const noexcept = default;
		std::partial_ordering operator<=>(const RenderPassFloatColorClearValues&) const noexcept = default;
	};

	struct RenderPassIntColorClearValues
	{
		int32_t r;
		int32_t g;
		int32_t b;
		int32_t a;

		RenderPassIntColorClearValues() = default;

		bool operator==(const RenderPassIntColorClearValues&) const noexcept = default;
		std::strong_ordering operator<=>(const RenderPassIntColorClearValues&) const noexcept = default;
	};

	struct RenderPassUIntColorClearValues
	{
		uint32_t r;
		uint32_t g;
		uint32_t b;
		uint32_t a;

		RenderPassUIntColorClearValues() = default;

		bool operator==(const RenderPassUIntColorClearValues&) const noexcept = default;
		std::strong_ordering operator<=>(const RenderPassUIntColorClearValues&) const noexcept = default;
	};

	struct RenderPassDepthStencilClearValues
	{
		float d;
		uint32_t s;

		RenderPassDepthStencilClearValues() = default;

		bool operator==(const RenderPassDepthStencilClearValues&) const noexcept = default;
		std::partial_ordering operator<=>(const RenderPassDepthStencilClearValues&) const noexcept = default;
	};
}