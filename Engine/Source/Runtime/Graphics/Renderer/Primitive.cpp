#include <Core/Common/Required.h>
#include <Graphics/Utils/Shader.h>
#include "Primitive.h"

#include <GL/glew.h>

using Graphics::Renderer::Primitive;

Primitive::Primitive ()
{
	
}

Primitive::~Primitive ()
{
	Destroy ();
}

void Primitive::Destroy ()
{}

void Primitive::Preprocess ()
{
	glClearColor(0.3f, 0.2f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Primitive::Render (uint32 vao, Shader & shader, uint32 texture = 69)
{
	shader.Bind();
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}