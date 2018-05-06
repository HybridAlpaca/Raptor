#define DEBUG_BUILD

#include <Core/Misc/Required.h>
#include <Renderer/Utils/Window.h>


int main (int argc, char * argv[])
{
	using Renderer::Utils::WindowController;
	
	WindowController window(640, 480, "[ dummy display ]");
	
	glClearColor(1.0f, 0.0f, 0.6f, 1.0f);
	
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	
		window.Update();
	}
	
}