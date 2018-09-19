#include <Raptor/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <Core/Plugins.h>
#include <Core/EngineApi.h>

using namespace Graphics;

namespace
{
	cchar vertex =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"  gl_Position = vec4(aPos, 1.0);\n"
		"}\0";

	cchar fragment =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"  FragColor = vec4(0.7f, 0.2f, 0.7f, 1.0);\n"
		"}\0";

	struct Vertex
	{
		float32 position [3];

		static VertexFormat format;

		static void Init ()
		{
			format
				.AddAttribute({ 3 })
				.End();
		}
	};

	VertexFormat Vertex::format;

	Vertex vertices [] =
	{
		{ 0.5f,   0.5f, 0.0f },
		{ 0.5f,  -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f,  0.5f, 0.0f }
	};

	uint32 indices [] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
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

	Display::Window window({ "Hello, Raptor!", 800, 600 });

	RenderDevice::Initialize({ true });

	RenderDevice::Resize(window.FrameWidth(), window.FrameHeight());

	plugin -> Init(Core::GetEngineApi);

	RenderResource shaders [] =
	{
		RenderDevice::AllocateShader(vertex,   ShaderType::VERTEX),
		RenderDevice::AllocateShader(fragment, ShaderType::FRAGMENT)
	};

	RenderResource program = RenderDevice::AllocateShaderProgram(shaders, 2);

	RenderDevice::DestroyShader(shaders[0]);
	RenderDevice::DestroyShader(shaders[1]);

	// Vertex Array & Buffer Creation

	Vertex::Init(); // Compile the vertex format

	RenderResource VAO, VBO, EBO;

	uint32 indexCount = sizeof(indices) / sizeof(indices[0]);

	BufferDescriptor vertDesc = { BufferType::VERTEX, sizeof(vertices), Vertex::format };
	BufferDescriptor idexDesc = { BufferType::INDEX,  sizeof(indices) };

	VAO = RenderDevice::AllocateVertexArray();
	VBO = RenderDevice::AllocateBuffer(VAO, vertices, vertDesc);
	EBO = RenderDevice::AllocateBuffer(VAO, indices, idexDesc);

	// Run

	while (!window.ShouldClose())
	{
		window.PollEvents();

		plugin -> Update();

		RenderDevice::DrawIndexed(program, VAO, indexCount, 0);

		window.SwapBuffers();
	}

	// Shut Down

	plugin -> Shutdown();

	RenderDevice::DestroyVertexArray(VAO);
	RenderDevice::DestroyBuffer(VBO);
	RenderDevice::DestroyBuffer(EBO);
	RenderDevice::DestroyShaderProgram(program);

	DestroyPlugin(plugin);

	lib.Close();

	return 0;
}
