#include "pch.h"
#include "VertexData.h"

std::vector<VertexData> vertices;
std::vector<uint16_t> indices;

bool VertexData::operator==(const VertexData& rhs) const noexcept
{
    if (position != rhs.position)
        return false;
    else
        return textureCoordinates == rhs.textureCoordinates;
}
