#include <Core/Common/Required.h>
#include <Graphics/Device/Display.h>

int16 main (int16 argc, cchar argv[])
{
	using Graphics::Device::Display;
	
	Display display(800, 600, "Demo Window");
	
	while (!display.Closed())
	{
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		display.Update();
	}
	
	return 0;
}