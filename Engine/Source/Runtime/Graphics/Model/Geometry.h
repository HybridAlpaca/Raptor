#pragma once

#include <Core/Common/Required.h>
#include <Graphics/Utils/Shader.h>

#include <glm/glm.hpp>

#include <vector>

namespace Graphics::Model
{

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec2 texCoord;
};

enum class TextureType
{
	DIFFUSE,
	NORMAL,
	SPECULAR,
	HEIGHT
};

struct Texture
{
	uint32 id;
	TextureType type;
	cchar path;
};

class Mesh
{
	std::vector<Texture> textures;

	uint32 vao;
	uint32 vbo;
	uint32 ebo;

	uint32 indexCount;

public:

	Mesh (const std::vector<Vertex> & vertices, const std::vector<uint32> & indices, const std::vector<Texture> & textures);
	Mesh (const Mesh & copy) = delete;
	~Mesh ();

	Mesh & operator= (const Mesh & rhs) = delete;

	void Draw (const Utils::Shader & shader) const;
};

}
