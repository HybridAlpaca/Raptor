#include <Core/Common/Required.h>
#include <Graphics/Device/Display.h>

/*
 * 
 * name: main
 * @param int32 argc, cchar argv[]]
 * @return int32
 * 
 */
 
int32 main (int32 argc, cchar argv[])
{
	using Graphics::Device::Display;
	
	Display display(800, 600, "Hello, World!");
	
	while (!display.Closed())
	{
		display.Clear(1.0f, 0.23f, 1.0f, 1.0f);
		display.Update();
	}
	
	return 0;
}
