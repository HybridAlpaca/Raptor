#include <Raptor/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <Core/Plugins.h>
#include <Core/EngineApi.h>

using namespace Graphics;

namespace
{
	cchar vertex =
	"#version 330 core"
	"void main ()"
	"{"
	"}";

	cchar fragment =
	"#version 330 core"
	"void main ()"
	"{"
	"}";

	float32 vertices [] =
	{
		1.0f, 1.0f, 1.0f
	};

	uint32 indices [] =
	{
		69, 420, 911
	};
}

int32 main (int32 argc, cchar * argv)
{
	// Open Library

	Core::SharedLibrary lib;
	lib.Open("/home/cellman123/Desktop/Raptor/Engine/Plugins/Basic/libbasic.so");

	Create_T  * CreatePlugin  = (Create_T  *) lib.ProcAddress("CreatePlugin");
  Destroy_T * DestroyPlugin = (Destroy_T *) lib.ProcAddress("DestroyPlugin");

	// Initialize

	Plugin * plugin = CreatePlugin();

	plugin -> Init(Core::GetEngineApi);

	Display::Window window({ "Hello, Raptor!", 800, 600 });

	// Run

	RenderDevice::Init();

	RenderResource shaders [2] =
	{
		RenderDevice::CreateShader(vertex, ShaderType::VERTEX),
		RenderDevice::CreateShader(fragment, ShaderType::FRAGMENT)
	};

	RenderResource program = RenderDevice::CreateProgram(shaders, 2);

	RenderResource vertexArray = RenderDevice::CreateVertexArray();

	BufferDescriptor descs [] =
	{
		{ BufferType::VERTEX, sizeof(vertices) },
		{ BufferType::INDEX, sizeof(indices) }
	};

	RenderResource buffers [] =
	{
		RenderDevice::CreateBuffer(vertexArray, vertices, descs[0]),
		RenderDevice::CreateBuffer(vertexArray, indices, descs[1])
	};

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
