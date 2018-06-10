#include <Core/Common/Required.h>
#include "Geometry.h"

#include <GL/glew.h>

#include <vector>

using Graphics::Model::Geometry;
using Graphics::Model::Vertex;

Geometry::Geometry (std::vector<Vertex> vertices, std::vector<uint32> indices)
{
	glGenVertexArrays(1, & vao);
	glGenBuffers(1, & vbo);
	glGenBuffers(1, & ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size(), & vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), & indices[0], GL_STATIC_DRAW);

	indexCount = indices.size();

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
	glEnableVertexAttribArray(0);
}

Geometry::~Geometry ()
{
	glDeleteVertexArrays(1, & vao);
	glDeleteBuffers(1, & vbo);
	glDeleteBuffers(1, & ebo);
}
