#include "RenderDevice.h"
#include "RenderState.h"
#include <Display.h>

#include <GL/glew.h>

using namespace Graphics;

namespace
{
	// file-local private information

	GL::RenderState state;
}

void Backend::Clear (float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Backend::Present (const Display & display)
{
	display.SwapBuffers();
}

void Backend::Resize (uint32 width, uint32 height)
{
	glViewport(0, 0, width, height);
}
