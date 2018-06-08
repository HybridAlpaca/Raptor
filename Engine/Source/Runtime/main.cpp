#include <Core/Common/Required.h>
#include <Core/Backend/Display.h>

#include <GL/glew.h>

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
	using Core::Backend::Display;
	using Core::Backend::DisplayConfig;

	DisplayConfig config;
	Display display(config);

	glClearColor(0.1f, 0.2f, 0.7f, 1.0f);
	while (display.Running())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		display.Update();
	}

	return 0;
}
