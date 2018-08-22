#include "CommandBufferStream.h"

using namespace Graphics;

CommandBufferStream::CommandBufferStream ()
{}

CommandBufferStream::~CommandBufferStream ()
{}

Commands::CommandPackage & CommandBufferStream::AllocateCommand ()
{
	Commands::CommandPackage & command = commandBuffer[indexWrite];

	/// This wonderful little snippet of code you're looking at
	/// uses a bit of Modulus magic to increment the write index
	/// and wrap it around to 0 if it overflows the command buffer.
	/// @todo assert the overflow never actually happens.
	indexWrite = (indexWrite + 1) & (MAX_RENDER_COMMANDS - 1);

	return command;
}
