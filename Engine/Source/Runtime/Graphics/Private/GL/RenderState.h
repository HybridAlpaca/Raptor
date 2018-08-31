#pragma once

#include <Core/Common/Required.h>
#include <GL/glew.h>

namespace Graphics::GL
{

	struct RenderState
	{
		GLuint boundVAO = 0;
		GLuint boundProgram = 0;

		GLuint programs [4096] = { 0 };
		uint32 numPrograms = 0;
	};

}
