#include "Mesh.h"

#include <GL/glew.h>

#include <string>
#include <iostream>

Mesh::Mesh (const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices, const std::vector<Texture> & textures)
: vertices (vertices)
, textures (textures)
{
	indexCount = indices.size();
	SetupMesh(indices);
}

void Mesh::SetupMesh (const std::vector<unsigned int> & indices)
{
	glGenVertexArrays(1, & VAO);
	glGenBuffers(1, & VBO);
	glGenBuffers(1, & EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), & vertices[0], GL_STATIC_DRAW);  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), & indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
	// vertex normals
	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texcoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));


	glBindVertexArray(0);
}

void Mesh::Draw (const Shader & shader) const
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int heightNr = 1;
	unsigned int normalNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string name;
		std::string number;
		TextureType type = textures[i].type;
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
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
