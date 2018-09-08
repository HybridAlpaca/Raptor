#include <Raptor/Required.h>

#include <Graphics/Commands.h>
#include <Graphics/Display.h>
#include <Graphics/RenderDevice.h>

#include <iostream>

namespace
{
	struct Vec3f
	{
		float32 x;
		float32 y;
		float32 z;
	};

	struct Color3f
	{
		float32 r;
		float32 g;
		float32 b;
	};

	struct Vertex
	{
		Vec3f position;
		Color3f color;
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
	format
		.AddAttribute({3}) // Stride and offset are implied
		.AddAttribute({3}) // Stride and offset are implied
		.End();            // Compile the vertex format

	BufferDescriptor vertDesc   = { BufferType::VERTEX, sizeof(vertices), format };
	BufferDescriptor idexDesc   = { BufferType::INDEX, sizeof(indices) };

	RenderResource vertexArray  = RenderDevice::AllocateVertexArray();
	RenderResource vertexBuffer = RenderDevice::AllocateBuffer(vertexArray, vertices, vertDesc);
	RenderResource indexBuffer  = RenderDevice::AllocateBuffer(vertexArray, indices, idexDesc);

	double previousTime = display.Time();
	uint16 frameCount = 0;

	while (!display.Closed())
	{
		// Listen

		display.PollEvents();

		// Draw

		Commands::Clear::Dispatch({ 0.2f, 0.2f, 0.2f, 1.0f });

		Commands::DrawIndexed::Dispatch({ shader, vertexArray, 6, 0 });

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

	RenderDevice::DestroyBuffer(indexBuffer);
	RenderDevice::DestroyBuffer(vertexBuffer);
	RenderDevice::DestroyVertexArray(vertexArray);
	RenderDevice::DestroyShaderProgram(shader);

	return 0;
}
