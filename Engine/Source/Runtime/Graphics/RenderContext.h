#pragma once

#include "CommandBufferStream.h"

namespace Graphics
{

class RenderContext
{
	CommandBufferStream stream;

public:

	RenderContext ();

	/// Temporarily non-copyable
	RenderContext (const RenderContext & copy) = delete;

	~RenderContext ();

	/// Temporarily non-copyable
	RenderContext & operator= (const RenderContext & rhs) = delete;

	void Clear (float r, float g, float b, float a = 1.0f);
	void DrawIndexed (unsigned int vertexArray, unsigned int indexCount);

	CommandBufferStream & InternalStream () { return stream; }
};

}
