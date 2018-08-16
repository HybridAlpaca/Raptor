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

void GLRenderDevice::Dispatch (const Commands::CommandPackage & package)
{
	switch (package.type)
	{
		case Commands::DRAW_INDEXED:
			glBindVertexArray(package.data.drawIndexed.vertexArray);
			glDrawElements(GL_TRIANGLES, package.data.drawIndexed.indexCount, GL_UNSIGNED_INT, 0);
			break;
	}
}
