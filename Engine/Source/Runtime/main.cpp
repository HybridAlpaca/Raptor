#include <Raptor/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>
#include <Graphics/Importer.h>

#include <Core/SharedLib.h>
#include <Core/EngineApi.h>

using namespace Core;
using namespace Graphics;

int32 main (int32 argc, cchar * argv)
{
	// Test Playgound Area

	{
		Importer importer("/home/cellman123/Desktop/Raptor/Engine/Assets/Models/");
		Model model = importer.Load("/home/cellman123/Desktop/Raptor/Engine/Assets/Models/nanosuit/nanosuit.obj");

		for (uint32 i = 0; i < model.meshCount; ++i)
		{
			delete [] model.meshes[i].vertices;
			delete [] model.meshes[i].indices;
		}
	}

	// Open Library

	SharedLibrary lib;
	lib.Open("/home/cellman123/Desktop/Raptor/Engine/Plugins/Basic/libbasic.so");

	const PluginDescriptor * desc = (PluginDescriptor *) lib.ProcAddress("Exports");

	// Initialize

	Plugin * plugin = desc -> CreatePlugin();

	Display::Window window({ "Hello, Raptor!", 800, 600 });

	RenderDevice::Initialize({ true });

	RenderDevice::Resize(window.FrameWidth(), window.FrameHeight());

	plugin -> Init(GetEngineApi);

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
