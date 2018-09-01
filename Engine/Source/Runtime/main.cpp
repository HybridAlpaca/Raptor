#include <Core/Common/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

cchar vertex =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

cchar fragment =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

float vertices [] =
	{
		-0.5f, -0.5f, 0.0f, // left
		0.5f, -0.5f, 0.0f, // right
		0.0f,  0.5f, 0.0f  // top
	};

int32 main (int32 argc, cchar * argv)
{
	using namespace Graphics;

	Display display
	({
		"Hello, Raptor!",
		800,
		600,
		3,
		3
	});

	Backend::Init();
	Backend::Resize(display.FrameWidth(), display.FrameHeight());

	ResourceHandle shader = Backend::AllocateShaderProgram(vertex, fragment);
	ResourceHandle vertexArray = Backend::AllocateVertexArray(vertices, sizeof(vertices));

	while (!display.Closed())
	{
		display.PollEvents();

		Backend::Clear(1.0f, 0.0f, 0.5f, 1.0f);
		Backend::Draw(shader, vertexArray, 3);
		Backend::Present(display);
	}

	Backend::DestroyVertexArray(vertexArray);
	Backend::DestroyShaderProgram(shader);

	return 0;
}
