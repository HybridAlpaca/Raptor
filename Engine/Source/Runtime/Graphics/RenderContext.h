#pragma once

#include "Commands.h"

namespace Graphics
{

const unsigned int MAX_RENDER_COMMANDS = 256; // approx 4 KiB per command buffer

class RenderContext
{
	unsigned int readIndex = 0;
	unsigned int writeIndex = 0;
	unsigned int commandCount = 0;

	/// Increments integer index and wraps around to 0 if value becomes too large
	inline void IncWrite ();

public:

	Commands::CommandPackage commandBuffer [MAX_RENDER_COMMANDS];

	RenderContext ();

	/// Temporarily non-copyable
	RenderContext (const RenderContext & copy) = delete;

	~RenderContext ();

	/// Temporarily non-copyable
	RenderContext & operator= (const RenderContext & rhs) = delete;

	///  AllocateCommand may likely be raplaced by separate functions per command type
	Commands::CommandPackage & AllocateCommand (Commands::CommandType type);

	inline unsigned int CommandCount () const { return commandCount; }

	void Clear ();
};

}
