#include "Shader.h"

#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

enum class TextureType
{
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT
};

struct Texture
{
	unsigned int id;
	TextureType type;
	const char * path;
};

class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	
	unsigned int VAO, VBO, EBO;
	unsigned int indexCount;
	
	void SetupMesh (const std::vector<unsigned int> & indices);

public:

	Mesh (const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices, const std::vector<Texture> & textures);

	void Draw (const Shader & shader) const;
};
