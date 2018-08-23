#include "RenderDevice.h"

#include <GL/glew.h>

using namespace Graphics;
using Graphics::Backend::GLRenderDevice;

GLRenderDevice::GLRenderDevice ()
{
	glEnable(GL_DEPTH_TEST);
}

GLRenderDevice::~GLRenderDevice ()
{}

void GLRenderDevice::Dispatch (const RenderContext & ctx)
{
	const Commands::CommandPackage * commands = ctx.InternalBuffer();

	for (unsigned int i = 0; i < ctx.BufferSize(); ++i)
	{
		const Commands::CommandPackage & command = commands[i];
		switch (command.type)
		{
			// Clear screen
			case Commands::CLEAR:
			{
				glClearColor(command.data.clear.r, command.data.clear.g, command.data.clear.b, command.data.clear.a);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;
			}
			// Indexed draw
			case Commands::DRAW_INDEXED:
			{
				if (boundVAO != command.resourceSlot)
				{
					glBindVertexArray(command.resourceSlot);
					boundVAO = command.resourceSlot;
				}
				glDrawElements(GL_TRIANGLES, command.data.drawIndexed.indexCount, GL_UNSIGNED_INT, 0);
				break;
			}
			// No operation
			case Commands::NOP:
			default:
				break;
		}
	}
}
