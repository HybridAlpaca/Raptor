#include <Raptor/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>
#include <Graphics/EngineApi.h>

#include <Core/SharedLib.h>
#include <Core/PluginsApi.h>

using namespace Core;
using namespace Graphics;

int32 main (int32 argc, cchar * argv)
{
	// Test Playgound Area

	// Open Library

	SharedLibrary lib;
	lib.Open("/home/cellman123/Desktop/Raptor/Engine/Plugins/Basic/libbasic.so");

	const PluginDescriptor * desc = (PluginDescriptor *) lib.ProcAddress("Exports");

	// Initialize

	Plugin * plugin = desc -> CreatePlugin();

	Display::Window window({ "Hello, Raptor!", 800, 600 });

	RenderDevice::Initialize({ true });

	RenderDevice::Resize(window.FrameWidth(), window.FrameHeight());

	ApiRegistry registry;

	Graphics::Api::EngineApi api;

	registry.RegisterApi(GRAPHICS_API, & api);

	plugin -> Init(registry);

	// Run

	float32 delta = 0.0f;	// Time between current frame and last frame
	float32 lastFrame = 0.0f;

	while (!window.ShouldClose())
	{
		window.PollEvents();

		float32 currentFrame = window.CurrentTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;

		plugin -> Update(delta);

		window.SwapBuffers();
	}

	// Shut Down

	plugin -> Shutdown();

	lib.Close();

	return 0;
}
