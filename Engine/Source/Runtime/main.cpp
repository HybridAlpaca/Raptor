#include <Raptor/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <Core/Plugins.h>
#include <Core/EngineApi.h>

using namespace Graphics;

int32 main (int32 argc, cchar const * argv)
{
	// Open Library

	Core::SharedLibrary lib;
	lib.Open("/home/cellman123/Desktop/Raptor/Engine/Plugins/Basic/libbasic.so");

	Create_T  * CreatePlugin  = (Create_T  *) lib.ProcAddress("CreatePlugin");
  Destroy_T * DestroyPlugin = (Destroy_T *) lib.ProcAddress("DestroyPlugin");

	// Initialize

	Plugin * plugin = CreatePlugin();

	Display::Window window({ "Hello, Raptor!", 800, 600 });

	RenderDevice::Initialize({ true });

	RenderDevice::Resize(window.FrameWidth(), window.FrameHeight());

	plugin -> Init(Core::GetEngineApi);

	// Run

	while (!window.ShouldClose())
	{
		window.PollEvents();

		plugin -> Update();

		window.SwapBuffers();
	}

	// Shut Down

	plugin -> Shutdown();

	DestroyPlugin(plugin);

	lib.Close();

	return 0;
}
