#include "Shader.h"

#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
};

enum class TextureType
{
	DIFFUSE,
	SPECULAR,
	NORMAL
};

struct Texture
{
	unsigned int id;
	TextureType type;
};

class Mesh
{
	unsigned int VAO, VBO, EBO;
	
	void SetupMesh ();

public:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh (std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture> textures);

	void Draw (const Shader & shader);
};
