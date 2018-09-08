#pragma once

#include <Raptor/Required.h>
#include <GL/glew.h>

namespace Graphics::GL
{
	class RenderState
	{
		GLuint boundVAO = 0; ///< The VAO bound to the OpenGL context
		GLuint boundVBO = 0;
		GLuint boundProgram = 0; ///< The shader program bound to the OpenGL context

	public:

		inline void BindVAO (GLuint VAO)
		{
			if (boundVAO != VAO)
			{
				glBindVertexArray(VAO);
				boundVAO = VAO;
			}
		}

		inline void BindProgram (GLuint program)
		{
			if (boundProgram != program)
			{
				glUseProgram(program);
				boundProgram = program;
			}
		}
	};
}
