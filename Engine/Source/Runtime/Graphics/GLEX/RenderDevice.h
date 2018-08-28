#pragma once

#include <GL/glew.h>

/*
 * EXPIREMENTAL RENDER DEVICE IMPLEMENTATION
 *
 * Please use with careful attention to detail, and be sure to notify HybridAlpaca of any bugs or suggestions.
 *
 */

namespace Graphics::Backend
{

class RenderDevice
{
	// GL state machine

	GLuint boundVAO;
	GLuint boundProgram;

	// GL GPU resources

	GLuint VAOList [MAX_RENDER_RESOURCES];
	GLuint ProgramList [MAX_RENDER_RESOURCES];

public:

	RenderDevice ();
	RenderDevice (const RenderDevice & copy) = delete;
	~RenderDevice ();

	RenderDevice & operator= (const RenderDevice & rhs) = delete;

	// State methods

	void BindVAO (GLuint VAO);

	// Draw methods

	void DrawElements (GLenum primitiveType, GLuint indexCount, GLenum indexType, GLuint indexOffset);
};

}
