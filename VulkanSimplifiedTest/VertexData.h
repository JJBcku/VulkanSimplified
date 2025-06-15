#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

struct VertexData
{
	glm::vec4 position;
	glm::vec2 textureCoordinates;
};

const std::vector<VertexData> vertices = {
	{{-0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f}},
	{{0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
	{{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f}},
	{{-0.5f, 0.5f, 0.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
};

struct UniformBufferData
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};