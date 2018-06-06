#include <Core/Common/Required.h>
#include <Graphics/Device/Display.h>

int16 main (int16 argc, cchar argv[])
{
	using Graphics::Device::Display;
	
	Display display(800, 600, "Hello, World!");
	
	float r = 0.0f;
	float b = 1.0f;
	float rd = 0.002f;
	float bd = -0.002f;
	
	while (!display.Closed())
	{
		r += rd;
		b += bd;
		if (r >= 1.0f)
		{
			r = 1.0f;
			rd = -rd;
		}
		if (r <= 0.0f)
		{
			r = 0.0f;
			rd = -rd;
		}
		if (b >= 1.0f)
		{
			b = 1.0f;
			bd = -bd;
		}
		if (b <= 0.0f)
		{
			b = 0.0f;
			bd = -bd;
		}
		display.Clear(r, 0.0f, b, 1.0f);
		display.Update();
	}
	
	return 0;
}