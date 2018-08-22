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

void GLRenderDevice::Dispatch (const CommandBufferStream & stream)
{
	const Commands::CommandPackage * commands = stream.InternalBuffer();

	for (unsigned int i = 0; i < stream.Size(); ++i)
	{
		const Commands::CommandPackage & command = commands[i];
		switch (command.type)
		{
			// No operation
			case Commands::NOP:
				break;
			// Clear screen
			case Commands::CLEAR:
				glClearColor(command.data.clear.r, command.data.clear.g, command.data.clear.b, command.data.clear.a);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;
			// Indexed draw
			case Commands::DRAW_INDEXED:
				if (boundVAO != command.data.drawIndexed.vertexArray)
				{
					glBindVertexArray(command.data.drawIndexed.vertexArray);
					boundVAO = command.data.drawIndexed.vertexArray;
				}
				glDrawElements(GL_TRIANGLES, command.data.drawIndexed.indexCount, GL_UNSIGNED_INT, 0);
				break;
		}
	}
}
