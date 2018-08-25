#include "DrawContext.h"

using namespace Graphics;

DrawContext::DrawContext ()
{
	// @todo: something
}

DrawContext::~DrawContext ()
{
	// @todo: revert something
}

Commands::DrawPackage & DrawContext::AllocateCommand ()
{
	Commands::DrawPackage & command = commandBuffer[indexWrite];

	/// This wonderful little snippet of code you're looking at
	/// uses a bit of Modulus magic to increment the write index
	/// and wrap it around to 0 if it overflows the command buffer.
	/// @todo assert the overflow never actually happens.
	indexWrite = (indexWrite + 1) & (MAX_RENDER_DRAW_COMMANDS - 1);

	return command;
}


void DrawContext::Clear (float r, float g, float b, float a)
{
	Commands::DrawPackage & command = AllocateCommand();
	command.type = Commands::Draw::CLEAR;
	command.data.clear.r = r;
	command.data.clear.g = g;
	command.data.clear.b = b;
	command.data.clear.a = a;
}

void DrawContext::DrawIndexed (unsigned int vertexArray, unsigned int indexCount)
{
	Commands::DrawPackage & command = AllocateCommand();
	command.type = Commands::Draw::DRAW_INDEXED;
	command.resourceSlot = vertexArray;
	command.data.drawIndexed.indexCount = indexCount;
}
