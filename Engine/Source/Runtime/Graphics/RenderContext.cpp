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

void RenderContext::Clear (float r, float g, float b, float a)
{
	Commands::CommandPackage & command = stream.AllocateCommand();
	command.type = Commands::CLEAR;
	command.data.clear.r = r;
	command.data.clear.g = g;
	command.data.clear.b = b;
	command.data.clear.a = a;
}

void RenderContext::DrawIndexed (unsigned int vertexArray, unsigned int indexCount)
{
	Commands::CommandPackage & command = stream.AllocateCommand();
	command.type = Commands::DRAW_INDEXED;
	command.data.drawIndexed.vertexArray = vertexArray;
	command.data.drawIndexed.indexCount = indexCount;
}
