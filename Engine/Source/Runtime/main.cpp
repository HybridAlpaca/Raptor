#include <Core/Common/Required.h>
#include <Graphics/RenderDevice.h>

int32 main (int32 argc, cchar * argv)
{
	Graphics::DisplayParams params =
	{
		"Hello, Raptor!",
		800,
		600,
		3,
		3
	};

	Graphics::Display display(params);

	Graphics::RenderDevice device(display);

	while (!display.Closed())
	{
		display.SwapBuffers();
		display.PollEvents();

		device.Clear(1.0f, 0.0f, 0.5f, 1.0f);
	}

	return 0;
}
