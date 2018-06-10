#include <Core/Common/Required.h>
#include <Graphics/Utils/Shader.h>
#include "Geometry.h"

#include <GL/glew.h>

#include <vector>

using Graphics::Model::Mesh;
using Graphics::Model::Vertex;
using Graphics::Model::TextureType;
using Graphics::Model::Texture;
using Graphics::Utils::Shader;

Mesh::Mesh (const std::vector<Vertex> & vertices, const std::vector<uint32> & indices, const std::vector<Texture> & textures)
:textures(textures)
{
	indexCount = indices.size();

	glGenVertexArrays(1, & vao);
	glGenBuffers(1, & vbo);
	glGenBuffers(1, & ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), & vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), & indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoord));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));

	glBindVertexArray(0);
}

Mesh::~Mesh ()
{
	glDeleteVertexArrays(1, & vao);
	glDeleteBuffers(1, & vbo);
	glDeleteBuffers(1, & ebo);
}

void Mesh::Draw (const Shader & shader) const
{
	uint32 diffuseCount = 1;
	uint32 normalCount = 1;
	uint32 specularCount = 1;
	uint32 heightCount = 1;

	for (uint32 i = 0; i < textures.size(); ++i)
	{
			glActiveTexture(GL_TEXTURE0 + i);

			TextureType type = textures[i].type;
			if (type == TextureType::DIFFUSE)
			{
				shader.Int(("texture_diffuse" + std::to_string(diffuseCount++)).c_str(), i);
			}
			else if (type == TextureType::SPECULAR)
			{
				shader.Int(("texture_specular" + std::to_string(specularCount++)).c_str(), i);
			}
			else if (type == TextureType::NORMAL)
			{
				shader.Int(("texture_normal" + std::to_string(normalCount++)).c_str(), i);
			}
			else if (type == TextureType::HEIGHT)
			{
				shader.Int(("texture_height" + std::to_string(heightCount++)).c_str(), i);
			}

			glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
