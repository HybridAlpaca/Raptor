#pragma once

#include <Raptor/Required.h>
#include <GL/glew.h>

namespace Graphics::GL
{

	struct RenderState
	{
		GLuint boundVAO = 0; ///< The VAO bound to the OpenGL context
		GLuint boundVBO = 0;
		GLuint boundProgram = 0; ///< The shader program bound to the OpenGL context
	};

}
