#include <Core/Common/Required.h>
#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

int32 main (int32 argc, cchar * argv)
{
	Graphics::Display display
	({
		"Hello, Raptor!",
		800,
		600,
		3,
		3
	});

	Graphics::RenderDevice device(display);

	while (!display.Closed())
	{
		display.PollEvents();

		device.Clear(1.0f, 0.0f, 0.5f, 1.0f);
		device.Present(display);
	}

	return 0;
}
