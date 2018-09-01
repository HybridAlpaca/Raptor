#include <Core/Common/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

cchar vertex =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec2 aUV;\n"
	"layout (location = 2) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(aPos, 1.0);\n"
	"  ourColor = aColor;\n"
	"}\0";

cchar fragment =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"  FragColor = vec4(ourColor, 1.0);\n"
	"}\0";

float vertices [] =
	{
		-0.5f, -0.5f,	0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left
		0.5f,	-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // right
		0.0f,	0.5f,	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // top
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

	VertexAttribute vertexAttributes [] =
	{{
		3, 8 // position
	},
	{
		2, 8
	},
	{
		3, 8 // color
	}};
	uint32 indices [] =
	{
		0, 1, 2
	};

	VertexArrayDescription desc;
	desc.vertices = vertices;
	desc.verticesSize = sizeof(vertices);
	desc.indices = indices;
	desc.indicesSize = sizeof(indices);
	desc.vertexAttributes = vertexAttributes;
	desc.bufferDescCount = 3;

	ResourceHandle vertexArray = Backend::AllocateVertexArray(desc);

	uint32 frameCount = 0;

	while (!display.Closed())
	{
		// Listen

		display.PollEvents();

		// Draw

		Backend::Clear(1.0f, 0.0f, 0.5f, 1.0f);
		Backend::DrawIndexed(shader, vertexArray, 3);

		// Debug

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

		// Present

		Backend::Present(display);
	}

	Backend::DestroyVertexArray(vertexArray);
	Backend::DestroyShaderProgram(shader);

	return 0;
}
