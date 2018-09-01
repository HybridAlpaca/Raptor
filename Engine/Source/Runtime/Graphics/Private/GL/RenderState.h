#pragma once

#include <Core/Common/Required.h>
#include <GL/glew.h>

namespace Graphics::GL
{

	struct RenderState
	{
		GLuint boundVAO = 0; ///< The VAO bound to the OpenGL context
		GLuint boundProgram = 0; ///< The shader program bound to the OpenGL context

		uint32 internalWidth = 0;	///< Cached internal resolution width
		uint32 internalHeight = 0; ///< Cached internal resolution height
	};

}
