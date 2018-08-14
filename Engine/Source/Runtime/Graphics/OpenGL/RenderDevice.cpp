#include "RenderDevice.h"
#include "../RenderResource.h"

#include <GL/glew.h>

using Graphics::Backend::GLRenderDevice;

GLRenderDevice::GLRenderDevice ()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

GLRenderDevice::~GLRenderDevice ()
{}

void GLRenderDevice::Dispatch (unsigned int VAO, unsigned int indexCount)
{
	if (boundVAO != VAO)
	{
		// the additional branch is less expensive than the API call
		glBindVertexArray(VAO);
		boundVAO = VAO;
	}
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
