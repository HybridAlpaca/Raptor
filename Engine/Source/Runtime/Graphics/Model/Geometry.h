#pragma once

#include <Core/Common/Required.h>

#include <vector>

namespace Graphics::Model
{

struct Vertex
{
	float x;
	float y;
	float z;

	Vertex (float x, float y, float z) : x(x), y(y), z(z) {};
};

struct Geometry
{
	uint32 vao;
	uint32 vbo;
	uint32 ebo;
	uint32 indexCount;

	Geometry (std::vector<Vertex> vertices, std::vector<uint32> indices);
	~Geometry ();
};

}
