#include <Core/Common/Required.h>

#include <Renderer/Utils/Window.h>
#include <Core/Memory/AssetManager.h>

int16 main (int16 argc, cchar argv[])
{
	using Renderer::Utils::WindowController;
	
	WindowController window(640, 480, "Placeholder Window");
	
	while (!window.ShouldClose())
	{
		window.Update();
	}
	
	return 0;
}