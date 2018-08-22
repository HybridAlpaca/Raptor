#pragma once

#include "../CommandBufferStream.h"

namespace Graphics::Backend
{

class GLRenderDevice
{
	unsigned int boundVAO;

public:

	GLRenderDevice ();
	~GLRenderDevice ();

	void Dispatch (const CommandBufferStream & stream);

	VertexArrayHandle CreateVertexArray ();
	void DestroyVertexArray (VertexArrayHandle vertexArray);
};

}
