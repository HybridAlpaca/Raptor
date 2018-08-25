#include "RenderDevice.h"
#include <Core/Common/Required.h>

#include <GL/glew.h>

using namespace Graphics;
using Graphics::Backend::GL::RenderDevice;

RenderDevice::RenderDevice ()
{
	glEnable(GL_DEPTH_TEST);
}

RenderDevice::~RenderDevice ()
{}

void RenderDevice::Dispatch (const DrawContext & ctx)
{
	const Commands::DrawPackage * commands = ctx.InternalBuffer();

	for (psize i = 0; i < ctx.BufferSize(); ++i)
	{
		const Commands::DrawPackage & command = commands[i];
		switch (command.type)
		{
			// Clear screen
			case Commands::Draw::CLEAR:
			{
				glClearColor(command.data.clear.r, command.data.clear.g, command.data.clear.b, command.data.clear.a);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;
			}
			// Indexed draw
			case Commands::Draw::DRAW_INDEXED:
			{
				if (state.boundVAO != command.resourceSlot)
				{
					glBindVertexArray(command.resourceSlot);
					state.boundVAO = command.resourceSlot;
				}
				glDrawElements(GL_TRIANGLES, command.data.drawIndexed.indexCount, GL_UNSIGNED_INT, 0);
				break;
			}
			// No operation
			case Commands::Draw::NOP:
			default:
				break;
		}
	}
}
