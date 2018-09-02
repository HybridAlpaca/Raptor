#include <Core/Common/Required.h>

#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

cchar vertex =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
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
		 0.5f,  0.5f,	0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f
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

	RenderDevice::Initialize();
	RenderDevice::Resize(display.FrameWidth(), display.FrameHeight());

	ResourceHandle shader = RenderDevice::AllocateShaderProgram(vertex, fragment);

	VertexAttribute vertexAttributes [] =
	{{
		3, 6 // position
	},
	{
		3, 6 // color
	}};
	uint32 indices [] =
	{
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	VertexArrayDescription desc;
	desc.vertices = vertices;
	desc.verticesSize = sizeof(vertices);
	desc.indices = indices;
	desc.indicesSize = sizeof(indices);
	desc.vertexAttributes = vertexAttributes;
	desc.bufferDescCount = 2;

	ResourceHandle vertexArray = RenderDevice::AllocateVertexArray(desc);

	uint32 frameCount = 0;

	while (!display.Closed())
	{
		// Listen

		display.PollEvents();

		// Draw

		RenderDevice::Clear(1.0f, 0.0f, 0.5f, 1.0f);
		RenderDevice::DrawIndexed(shader, vertexArray, 6, 0);

		// Debug

		if ((++frameCount) == 60)
		{
			frameCount = 0;

			// Dump render device debug info
			FrameStats frameStats = RenderDevice::CurrentFrameStats();
			std::cout << "CALLS: " << (frameStats.APICallCount) << ", ";
			std::cout << "ERRORS: " << (frameStats.APICallErrors) << ", ";
			std::cout << "HITS: " << frameStats.CalcDrawCacheHits() << ", ";
			std::cout << "MISSES: " << (frameStats.drawCacheMisses) << ", ";
			std::cout << "TOTAL: " << (frameStats.drawCacheAccesses) << '\n';
		}

		// Present

		RenderDevice::Present(display);
	}

	RenderDevice::DestroyVertexArray(vertexArray);
	RenderDevice::DestroyShaderProgram(shader);

	return 0;
}
