#include <RenderDevice.h>
#include <Commands.h>

#include <GL/glew.h>

using namespace Graphics;

CmdDispatch * ClearCmd::dispatch = RenderDevice::Clear;

void RenderDevice::Init ()
{
	glewExperimental = true;
	glewInit();

	glViewport(0, 0, 800, 600);
}

void RenderDevice::Clear (void * data)
{
	ClearCmd * cmd = static_cast<ClearCmd *>(data);

	// glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
