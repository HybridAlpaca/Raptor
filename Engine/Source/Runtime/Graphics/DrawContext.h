#pragma once

#include "Commands.h"
#include "Constants.h"
#include <Core/Common/Required.h>

namespace Graphics
{

class DrawContext
{
	DrawPacket commandBuffer [MAX_RENDER_DRAW_COMMANDS];

	uint16 indexWrite;

	DrawPacket & AllocateCommand ();

public:

	DrawContext ();

	/// Temporarily non-copyable
	DrawContext (const DrawContext & copy) = delete;

	~DrawContext ();

	/// Temporarily non-copyable
	DrawContext & operator= (const DrawContext & rhs) = delete;

	/// Clear the framebuffer with the specified color
	void Clear (float r, float g, float b, float a = 1.0f);

	/// Perform an indexed draw call
	void DrawIndexed (unsigned int vertexArray, unsigned int indexCount);

	/// Access the internal CommandBufferStream
	inline const DrawPacket * InternalBuffer () const { return commandBuffer; }

	inline unsigned int BufferSize () const { return indexWrite; }
	inline void ClearBuffer () { indexWrite = 0; }
};

}
