#include <Raptor/Required.h>
#include <Raptor/Vector3.h>

#include <Core/JsUtil.h>
#include <Core/Functions.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

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
}

int32 main (int32 argc, cchar * argv)
{
	// Expiremental Javascript Engine

	v8::Locker locker;
	v8::HandleScope scope;

	v8::Handle<v8::ObjectTemplate> globalTemplate = v8::ObjectTemplate::New();

	globalTemplate -> Set(v8::String::New("RAPTOR"), v8::Boolean::New(true));
	globalTemplate -> Set(v8::String::New("print"), v8::FunctionTemplate::New(JS::Print));

	v8::Handle<v8::Context> context = v8::Context::New(nullptr, globalTemplate);

	v8::Handle<v8::String> source = JS::ReadFile(
		"/home/cellman123/Desktop/Raptor/Engine/Plugins/startup.js"
	);

	v8::Context::Scope contextScope(context);

	v8::Handle<v8::Script> script = v8::Script::Compile(source, v8::String::New("FILE"));

	script -> Run();

	v8::Handle<v8::Object> global = context -> Global();

	global -> Set (v8::String::New("VERSION"), v8::Number::New(0.1));

	v8::Handle<v8::Value> initFunc = global -> Get(v8::String::New("Init"));
	if (initFunc -> IsFunction())
	{
		v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(initFunc);

		v8::Handle<v8::Value> args[2];

		args[0] = v8::String::New("value1");
		args[1] = v8::String::New("value2");

		func -> Call(global, 2, args);
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

	while (!Display::Closed(window))
	{
		// Listen

		Display::PollEvents();

		// Debug

		float32 FPS = 60.0f; // sshhhh.... ;)

		v8::Handle<v8::Value> updateFunc = global -> Get(v8::String::New("Update"));
		if (updateFunc -> IsFunction())
		{
			v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(updateFunc);

			v8::Handle<v8::Value> args[1];

			args[0] = v8::Number::New(FPS);

			func -> Call(global, 1, args);
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
