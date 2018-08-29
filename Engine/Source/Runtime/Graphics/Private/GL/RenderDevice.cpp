#include "RenderDevice.h"

#include <GL/glew.h>

using namespace Graphics::GL;

RenderDevice::RenderDevice (const Display & display)
{
	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, display.FrameWidth(), display.FrameHeight());
}

RenderDevice::~RenderDevice ()
{
	// destructor
}

void RenderDevice::Clear (float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
