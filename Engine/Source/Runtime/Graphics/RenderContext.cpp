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

void RenderContext::IncWrite ()
{
	writeIndex = (writeIndex + 1) & (MAX_RENDER_COMMANDS - 1);

	/// @todo figure out why the fuck this is necessary...
	++commandCount;
	++commandCount;
}

Commands::CommandPackage & RenderContext::AllocateCommand (Commands::CommandType type)
{
	IncWrite();
	commandBuffer[writeIndex].type = type;
	commandBuffer[writeIndex].resourceSlot = 0x000000;
	return commandBuffer[writeIndex];
}

void RenderContext::Clear ()
{
	commandCount = 0;
	writeIndex = 0;
}
