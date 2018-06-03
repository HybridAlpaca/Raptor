#include <Core/Common/Required.h>
#include <Renderer/Utils/Window.h>

int16 main (int16 argc, cchar argv[])
{
	using namespace Renderer::Utils;
	
	WindowController window(640, 480, "Placeholder Window");
	
	while (!window.ShouldClose())
	{
		window.Update();
	}
	
	window.Destroy();
	
	return 0;
}