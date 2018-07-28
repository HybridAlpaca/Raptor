#include "Renderer.h"

#include <GL/glew.h>

#include <string>

Renderer::Renderer ()
{}

Renderer::~Renderer ()
{}

void Renderer::Render (const Mesh & mesh, const Shader & shader) const
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int heightNr = 1;
	unsigned int normalNr = 1;
	for (unsigned int i = 0; i < mesh.textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string name;
		std::string number;
		TextureType type = mesh.textures[i].type;
		if (type == TextureType::DIFFUSE)
		{
			name = "diffuse";
			number = std::to_string(diffuseNr++);
		}
		else if (type == TextureType::SPECULAR)
		{
			name = "specular";
			number = std::to_string(specularNr++);
		}
		else if (type == TextureType::NORMAL)
		{
			name = "normal";
			number = std::to_string(normalNr++);
		}
		else if (type == TextureType::HEIGHT)
		{
			name = "height";
			number = std::to_string(heightNr++);
		}

		shader.Int(("texture_" + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
	}

	// draw mesh
	glBindVertexArray(mesh.VAO);
	glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
