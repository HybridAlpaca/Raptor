#pragma once

#include "../RenderContext.h"

namespace Graphics::Backend
{

class GLRenderDevice
{
	unsigned int boundVAO;

public:

	GLRenderDevice ();
	~GLRenderDevice ();

	void Dispatch (const RenderContext & ctx);
};

}
