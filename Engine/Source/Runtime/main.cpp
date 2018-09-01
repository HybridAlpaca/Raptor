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
		3,
		1
	});

	Backend::Initialize();
	Backend::Resize(display.FrameWidth(), display.FrameHeight());

	ResourceHandle shader = Backend::AllocateShaderProgram(vertex, fragment);

	VertexBufferDescription bufferDesc =
	{
		0,
		3,
		0
	};
	VertexArrayDescription desc;
	desc.data = vertices;
	desc.size = sizeof(vertices);
	desc.vertexBufferDesc = & bufferDesc;
	desc.bufferDescCount = 1;

	ResourceHandle vertexArray = Backend::AllocateVertexArray(desc);

	uint32 frameCount = 0;

	while (!display.Closed())
	{
		display.PollEvents();

		Backend::Clear(1.0f, 0.0f, 0.5f, 1.0f);
		Backend::Draw(shader, vertexArray, 3);

		if ((++frameCount) == 60)
		{
			frameCount = 0;

			// Dump render device debug info
			FrameStats frameStats = Backend::CurrentFrameStats();
			std::cout << "CALLS: " << (frameStats.APICallCount) << ", ";
			std::cout << "ERRORS: " << (frameStats.APICallErrors) << ", ";
			std::cout << "HITS: " << frameStats.CalcDrawCacheHits() << ", ";
			std::cout << "MISSES: " << (frameStats.drawCacheMisses) << ", ";
			std::cout << "TOTAL: " << (frameStats.drawCacheAccesses) << '\n';
		}

		Backend::Present(display);
	}

	Backend::DestroyVertexArray(vertexArray);
	Backend::DestroyShaderProgram(shader);

	return 0;
}
