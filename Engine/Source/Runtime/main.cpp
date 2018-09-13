#include <Raptor/Required.h>
#include <Raptor/Vector3.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Graphics;
using namespace Raptor;

namespace
{
	struct Vertex
	{
		Vector3f position;
	};

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

		struct Memory
		{
			void * data  = nullptr;
			uintptr size = 0;
			uint32 count = 0;
		};

		class Mesh
		{
			RenderResource
				VAO,
				VBO,
				EBO;

			uint32 indexCount;

		public:

			Mesh (const VertexFormat & fmt, const Memory & vertices, const Memory & indices)
			{
				BufferDescriptor vertDesc   = { BufferType::VERTEX, vertices.size, fmt };
				BufferDescriptor idexDesc   = { BufferType::INDEX,  indices.size };

				VAO = RenderDevice::AllocateVertexArray();
				VBO = RenderDevice::AllocateBuffer(VAO, vertices.data, vertDesc);
				EBO = RenderDevice::AllocateBuffer(VAO, indices.data, idexDesc);

				indexCount = indices.count;
			}

			~Mesh ()
			{
				RenderDevice::DestroyVertexArray(VAO);
				RenderDevice::DestroyBuffer(VBO);
				RenderDevice::DestroyBuffer(EBO);
			}

			void Draw (RenderResource program, float32 color [4])
			{
				RenderDevice::ShaderUniform(program, "color", color);
				RenderDevice::DrawIndexed(program, VAO, indexCount, 0);
			}
		};
}

int32 main (int32 argc, cchar * argv)
{
	// Display & Swapchain Creation

	Display display
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

	RenderDevice::Resize(display.FrameWidth(), display.FrameHeight());

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

	VertexFormat format;
	format
		.AddAttribute({ 3 }) // Stride and offset are implied
		.End();            // Compile the vertex format

	Mesh mesh
	(
		format,
		{ vertices, sizeof(vertices) },
		{ indices, sizeof(indices), sizeof(indices) / sizeof(indices[0]) }
	);

	// Uniforms and Dynamic Render Data

	float32 clear [4] { 0.2f, 0.2f, 0.2f, 1.0f };
	float32 color [3] { 1.0f, 0.2f, 0.5f };

	// Debug Variables

	const uint32 fpsBufferSize = 20;
	float32 fps [fpsBufferSize] { 0 };

	ImGui::GetIO().IniFilename = "./Engine/Config/imgui.ini";

	while (!display.Closed())
	{
		// Listen

		display.PollEvents();

		// Debug

		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Debug");

			if (ImGui::Button("Quit")) { display.Close(); }

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

		mesh.Draw(program, color);

		// Present

		RenderDevice::Present(display);
	}

	// Resource Destruction

	RenderDevice::DestroyShaderProgram(program);

	return 0;
}
