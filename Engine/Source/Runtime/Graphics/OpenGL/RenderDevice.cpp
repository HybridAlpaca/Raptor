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

void GLRenderDevice::Dispatch (const RenderContext & ctx)
{
	for (unsigned int i = 0; i < ctx.CommandCount(); ++i)
	{
		Commands::CommandPackage package = ctx.commandBuffer[i];
		switch (package.type)
		{
			case Commands::NOP:
				break;
			case Commands::DRAW_INDEXED:
				glBindVertexArray(package.data.drawIndexed.vertexArray);
				glDrawElements(GL_TRIANGLES, package.data.drawIndexed.indexCount, GL_UNSIGNED_INT, 0);
				break;
		}
	}
}
