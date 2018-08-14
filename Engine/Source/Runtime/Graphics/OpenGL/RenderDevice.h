#pragma once

namespace Graphics::Backend
{

class GLRenderDevice
{
	unsigned int boundVAO;

public:

	GLRenderDevice ();
	~GLRenderDevice ();

	void Dispatch (unsigned int VAO, unsigned int indexCount);
};

}
