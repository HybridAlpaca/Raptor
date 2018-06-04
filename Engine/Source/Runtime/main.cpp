#include <Core/Common/Required.h>
#include <Graphics/Utils/Window.h>

int16 main (int16 argc, cchar argv[])
{
	using namespace Graphics::Utils;
	
	WindowController window(640, 480, "Placeholder Window");
	
	while (!window.ShouldClose())
	{
		window.Update();
	}
	
	window.Destroy();
	
	return 0;
}