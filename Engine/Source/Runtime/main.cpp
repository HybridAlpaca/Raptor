#include <Core/Common/Required.h>

#include <Graphics/Commands.h>
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

	RenderResource shader = RenderDevice::AllocateShaderProgram(vertex, fragment);

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

	RenderResource vertexArray = RenderDevice::AllocateVertexArray(desc);

	uint32 frameCount = 59;

	while (!display.Closed())
	{
		// Listen

		display.PollEvents();

		// Draw

		Commands::Clear clear = {0.2f, 0.2f, 0.2f, 1.0f};
		Commands::Clear::Dispatch(clear);

		Commands::DrawIndexed draw = {shader, vertexArray, 6, 0};
		Commands::DrawIndexed::Dispatch(draw);

		// Debug

		if ((++frameCount) == 60)
		{
			frameCount = 0;

			// Dump render device debug info
			RenderStats stats = RenderDevice::Stats();
			std::cout << "RenderStats (" << stats.width << "x" << stats.height << ") ";
			std::cout << (stats.drawCalls + stats.resourceCalls) << " Total Calls, " << stats.APICallErrors << " Errors, (";
			std::cout << stats.drawCacheMisses << " / " << stats.drawCacheAccesses << ") Cache Miss\n";
		}

		// Present

		RenderDevice::Present(display);
	}

	RenderDevice::DestroyVertexArray(vertexArray);
	RenderDevice::DestroyShaderProgram(shader);

	return 0;
}
