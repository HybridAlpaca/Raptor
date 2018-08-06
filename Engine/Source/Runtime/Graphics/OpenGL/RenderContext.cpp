#include "RenderContext.h"

#include <GL/glew.h>

using GL::RenderContext;

RenderContext::RenderContext ()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		// ERROR
		return;
	}
	
	initialized = true;
}

RenderContext::~RenderContext ()
{
	// TODO
}

void RenderContext::Clear (unsigned int FBO, bool clearColor, bool clearDepth, bool clearStencil, const glm::vec4 & color, unsigned int stencil)
{
	BindFBO(FBO);
	
	unsigned int flags = 0;
	
	if (clearColor)
	{
		flags |= GL_COLOR_BUFFER_BIT;
		glClearColor(color.x, color.y, color.z, color.w);
	}
	if (clearDepth)
	{
		flags |= GL_DEPTH_BUFFER_BIT;
	}
	if (clearStencil)
	{
		flags |= GL_STENCIL_BUFFER_BIT;
		// TODO set stencil mask
	}
	
	glClear(flags);
}

void RenderContext::Draw (unsigned int FBO, unsigned int VAO, unsigned int shader, const DrawCommand & command, unsigned int elementCount)
{
	BindFBO(FBO);
	BindShader(shader);
	BindVAO(VAO);
	glDrawElements((unsigned int) command.primitiveType, elementCount, GL_UNSIGNED_INT, 0);
}

void RenderContext::BindFBO (unsigned int FBO)
{
	if (FBO == boundFBO) return;
	
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	boundFBO = FBO;
}

void RenderContext::BindVAO (unsigned int VAO)
{
	if (VAO == boundVAO) return;
	
	glBindVertexArray(VAO);
	boundVAO = VAO;
}

void RenderContext::BindShader (unsigned int shader)
{
	if (shader == boundShader) return;
	
	glUseProgram(shader);
	boundShader = shader;
}
