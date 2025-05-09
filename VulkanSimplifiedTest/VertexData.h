#pragma once

#include <glm/vec4.hpp>

struct VertexData
{
	glm::vec4 position;
	glm::vec4 color;
};

const std::vector<VertexData> vertices = {
	{{0.0f, -0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
	{{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
};