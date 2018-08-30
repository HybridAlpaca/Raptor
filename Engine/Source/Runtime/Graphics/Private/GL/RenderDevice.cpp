#include "RenderDevice.h"
#include <Display.h>

#include <GL/glew.h>

using namespace Graphics::GL;

RenderDevice::RenderDevice (const Display & display)
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		/// @todo Log error
		return;
	}

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

void RenderDevice::Present (const Display & display)
{
	display.SwapBuffers();
}
