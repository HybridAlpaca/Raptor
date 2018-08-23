#include "RenderContext.h"

using namespace Graphics;

RenderContext::RenderContext ()
{
	// @todo: something
}

RenderContext::~RenderContext ()
{
	// @todo: revert something
}

Commands::CommandPackage & RenderContext::AllocateCommand ()
{
	Commands::CommandPackage & command = commandBuffer[indexWrite];

	/// This wonderful little snippet of code you're looking at
	/// uses a bit of Modulus magic to increment the write index
	/// and wrap it around to 0 if it overflows the command buffer.
	/// @todo assert the overflow never actually happens.
	indexWrite = (indexWrite + 1) & (MAX_RENDER_COMMANDS - 1);

	return command;
}


void RenderContext::Clear (float r, float g, float b, float a)
{
	Commands::CommandPackage & command = AllocateCommand();
	command.type = Commands::CLEAR;
	command.data.clear.r = r;
	command.data.clear.g = g;
	command.data.clear.b = b;
	command.data.clear.a = a;
}

void RenderContext::DrawIndexed (unsigned int vertexArray, unsigned int indexCount)
{
	Commands::CommandPackage & command = AllocateCommand();
	command.type = Commands::DRAW_INDEXED;
	command.resourceSlot = vertexArray;
	command.data.drawIndexed.indexCount = indexCount;
}
