#include <Raptor/Required.h>
#include <Raptor/Vector3.h>

#include <Core/JsUtil.h>
#include <Core/Functions.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Raptor;
using namespace Core;
using namespace Graphics;

namespace
{
	struct Vertex
	{
		Vector3f position;

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
		{ {0.5f,   0.5f, 0.0f} },
		{ {0.5f,  -0.5f, 0.0f} },
		{ {-0.5f, -0.5f, 0.0f} },
		{ {-0.5f,  0.5f, 0.0f} }
	};

	uint32 indices [] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

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
		"uniform vec3 color;\n"
		"void main()\n"
		"{\n"
		"  FragColor = vec4(color, 1.0);\n"
		"}\0";

	cchar script =
		"var i = 42;"
		"print(i);"
		"print('yeet')";
}

int32 main (int32 argc, cchar * argv)
{
	// Expiremental Javascript Engine

	{
		v8::Locker locker;
		v8::HandleScope scope;

		v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();

		global -> Set(v8::String::New("print"), v8::FunctionTemplate::New(JS::Print));

		v8::Handle<v8::Context> context = v8::Context::New(nullptr, global);

		JS::ExecuteString(context, script, "FILENAME");
	}

	// Display & Swapchain Creation

	Display::WindowHandle window = Display::Create
	({
		.title          = "Hello, Raptor!",
		.width          = 800,
		.height         = 600,
		.vsync          = 1,
		.fullscreen     = false,
		.glVersionMajor = 3,
		.glVersionMinor = 3
	});

	// Render Device Initialization

	RenderDevice::Initialize
	({
		.debug = true
	});

	RenderDevice::Resize(Display::FrameWidth(window), Display::FrameHeight(window));

	// Shader Program Creation

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

	BufferDescriptor vertDesc   = { BufferType::VERTEX, sizeof(vertices), Vertex::format };
	BufferDescriptor idexDesc   = { BufferType::INDEX,  sizeof(indices) };

	VAO = RenderDevice::AllocateVertexArray();
	VBO = RenderDevice::AllocateBuffer(VAO, vertices, vertDesc);
	EBO = RenderDevice::AllocateBuffer(VAO, indices, idexDesc);

	// Uniforms and Dynamic Render Data

	float32 clear [4] { 0.2f, 0.2f, 0.2f, 1.0f };
	float32 color [3] { 1.0f, 0.2f, 0.5f };

	// Debug Variables

	const uint32 fpsBufferSize = 20;
	float32 fps [fpsBufferSize] { 0 };

	ImGui::GetIO().IniFilename = "./Engine/Config/imgui.ini";

	while (!Display::Closed(window))
	{
		// Listen

		Display::PollEvents();

		// Debug

		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Debug");

			if (ImGui::Button("Quit")) { Display::Close(window); }

			float32 FPS = ImGui::GetIO().Framerate;

			for (uint32 i = 0; i < fpsBufferSize - 1; ++i) { fps[i] = fps[i + 1]; }

			fps[fpsBufferSize - 1] = FPS;

			ImGui::PlotLines("FPS", fps, fpsBufferSize, 0, "0 - 60", 0, 60);

			ImGui::ColorEdit4("Clear Color", clear);
			ImGui::ColorEdit3("Quad Color", color);

			ImGui::End();
		}

		// Draw

		RenderDevice::Clear(clear);

		RenderDevice::ShaderUniform(program, "color", color);
		RenderDevice::DrawIndexed(program, VAO, indexCount, 0);

		// Present

		Display::SwapBuffers(window);
	}

	// Resource Destruction

	RenderDevice::DestroyVertexArray(VAO);
	RenderDevice::DestroyBuffer(VBO);
	RenderDevice::DestroyBuffer(EBO);
	RenderDevice::DestroyShaderProgram(program);

	return 0;
}
