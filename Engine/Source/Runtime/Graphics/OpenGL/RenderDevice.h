#pragma once

#include "../Commands.h"

namespace Graphics::Backend
{

class GLRenderDevice
{
	unsigned int boundVAO;

public:

	GLRenderDevice ();
	~GLRenderDevice ();

	void Dispatch (const Commands::CommandPackage & package);

	VertexArrayHandle CreateVertexArray ();
	void DestroyVertexArray (VertexArrayHandle vertexArray);
};

}
