#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

struct VertexData
{
	glm::vec4 position;
	glm::vec2 textureCoordinates;

	bool operator==(const VertexData& rhs) const noexcept;
};

extern std::vector<VertexData> vertices;

extern std::vector<uint16_t> indices;

struct UniformBufferData
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};