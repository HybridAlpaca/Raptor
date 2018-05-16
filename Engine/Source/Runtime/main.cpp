#include <Core/Misc/Required.h>

#include <Renderer/Utils/Window.h>

int main (int argc, char * argv[])
{
	using Renderer::Utils::WindowController;
	
	WindowController window(640, 480, "[ dummy display ]");
	
	while (!window.ShouldClose())
	{
		window.Update();
	}
}