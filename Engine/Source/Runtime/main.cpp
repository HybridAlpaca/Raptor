#include <Core/Common/Required.h>
#include <Graphics/Device/Display.h>

int32 main (int32 argc, cchar argv[])
{
	using Graphics::Device::Display;
	
	Display display(800, 600, "Hello, World!");
	
	while (!display.Closed())
	{
		display.Clear(0.8f, 0.0f, 0.8f, 1.0f);
		display.Update();
	}
	
	return 0;
}
