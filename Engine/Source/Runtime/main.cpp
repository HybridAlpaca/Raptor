#include <Raptor/Required.h>

#include <Graphics/Commands.h>
#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

namespace
{
	struct Vertex
	{
		float32 position[3];
		float32 color[3];
	};

	Vertex vertices [] =
	{
		{ {0.5f,   0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} },
		{ {0.5f,  -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f} },
		{ {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} },
		{ {-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f} }
	};

	uint32 indices [] =
	{
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

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
}

int32 main (int32 argc, cchar * argv)
{
	using namespace Graphics;

	Display display
	({
		"Hello, Raptor!",
		640,
		480,
		3,
		3,
		1
	});

	RenderDevice::Initialize({true});
	RenderDevice::Resize(display.FrameWidth(), display.FrameHeight());

	RenderResource shader = RenderDevice::AllocateShaderProgram(vertex, fragment);

	VertexFormat format;

	format.verticesSize = sizeof(vertices);
	format.indicesSize = sizeof(indices);

	format
		.AddAttribute({3}) // stride and offset are implied
		.AddAttribute({3}) // stride and offset are implied
		.End(); // Compile the vertex format

	RenderResource vertexArray = RenderDevice::AllocateVertexArray();
	RenderResource vertexBuffer = RenderDevice::AllocateVertexBuffer(vertexArray, vertices, format);
	RenderResource indexBuffer = RenderDevice::AllocateIndexBuffer(vertexArray, indices, sizeof(indices));

	double previousTime = display.Time();
	uint16 frameCount = 0;

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

		{
			// Measure speed
			double currentTime = display.Time();
			++frameCount;
			// If a second has passed.
			if (currentTime - previousTime >= 1.0)
			{
				std::cout << "DEBUG - " << frameCount << '\n';

				frameCount = 0;
				previousTime = currentTime;
			}
		}

		// Present

		RenderDevice::Present(display);
	}

	RenderDevice::DestroyVertexArray(indexBuffer);
	RenderDevice::DestroyVertexArray(vertexBuffer);
	RenderDevice::DestroyVertexArray(vertexArray);
	RenderDevice::DestroyShaderProgram(shader);

	return 0;
}
