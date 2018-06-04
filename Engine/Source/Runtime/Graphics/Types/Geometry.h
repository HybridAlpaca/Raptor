#pragma once

#include <Core/Common/Required.h>

namespace Graphics::Types
{

struct Geometry
{
	uint32 vao;
	uint32 indexCount;
};

struct Material
{
	uint32 shader;
	// properties
	float shininess;
	// textures
	uint32 diffuse;
	uint32 normal;
	uint32 specular;
};

}