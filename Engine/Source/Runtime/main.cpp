#include <Core/Common/Required.h>
#include <Core/Backend/Application.h>
#include <Core/Backend/InputHandler.h>
#include <Graphics/Device/Display.h>

/*
 * 
 * name: main
 * @param int32 argc, cchar argv[]]
 * @return int32
 * 
 * TODO: Separate platform-dependant implementations
 * I.E. One file with `main` for *nix OS's, and one
 * with `WinMain` for win32 and win64.  Then, create
 * a separate init file with an entry point specified
 * to the linker, which would include the appropriate
 * function at compile time.
 * 
 */
int32 main (int32 argc, cchar argv[])
{
	using Graphics::Device::Display;
	using Core::Backend::Application;
	using Core::Backend::InputHandler;
	
	Application app;
	
	InputHandler input(app);
	Display display(app, 800, 600, "Hello, World!");
	
	while (app.running) // <-- don't like this syntax
	{
		input.Update();
		display.Clear(1.0f, 0.23f, 1.0f, 1.0f);
		display.Update();
	}
	
	return 0;
}
