#pragma once

#include "Commands.h"

namespace Graphics
{

class CommandBufferStream
{
	static const int MAX_RENDER_COMMANDS = 256;

	Commands::CommandPackage commandBuffer [MAX_RENDER_COMMANDS];

	unsigned int indexRead;
	unsigned int indexWrite;

public:

	CommandBufferStream ();
	CommandBufferStream (const CommandBufferStream & copy); // @todo
	~CommandBufferStream ();

	CommandBufferStream & operator= (const CommandBufferStream & rhs); // @todo

	Commands::CommandPackage & AllocateCommand ();
	inline const Commands::CommandPackage * InternalBuffer () const { return commandBuffer; }

	inline unsigned int Size () const { return indexWrite; }

	inline void Clear ()
	{
		indexRead = 0;
		indexWrite = 0;
	}
};

}
