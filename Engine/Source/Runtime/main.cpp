#include <Core/Common/Required.h>
#include <Core/Backend/Display.h>

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

	while (display.Running())
	{
		display.Update();
	}

	return 0;
}
