#pragma once

#include "Commands.h"

namespace Graphics
{

class RenderContext
{
	static const int MAX_RENDER_COMMANDS = 256;

	Commands::CommandPackage commandBuffer [MAX_RENDER_COMMANDS];

	unsigned int indexWrite;

	Commands::CommandPackage & AllocateCommand ();

public:

	RenderContext ();

	/// Temporarily non-copyable
	RenderContext (const RenderContext & copy) = delete;

	~RenderContext ();

	/// Temporarily non-copyable
	RenderContext & operator= (const RenderContext & rhs) = delete;

	/// Clear the framebuffer with the specified color
	void Clear (float r, float g, float b, float a = 1.0f);

	/// Perform an indexed draw call
	void DrawIndexed (unsigned int vertexArray, unsigned int indexCount);

	/// Access the internal CommandBufferStream
	inline const Commands::CommandPackage * InternalBuffer () const { return commandBuffer; }

	inline unsigned int BufferSize () const { return indexWrite; }
	inline void ClearBuffer () { indexWrite = 0; }
};

}
