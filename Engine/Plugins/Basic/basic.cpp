#include <Core/PluginsApi.h>

#include <iostream>

namespace
{
	float32 vertices [] =
	{
		0.5f,   0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	uint32 indices [] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	uint8 attribs [] =
	{
		3, 0, 0
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
		"void main()\n"
		"{\n"
		"  FragColor = vec4(0.7, 0.3, 0.7, 1.0);\n"
		"}\0";
}

class BasicPlugin : public Plugin
{
	GraphicsApi * graphics = nullptr;

	const uint32 GRAPHICS_API_VERSION = 0;

	float32 clearColor [4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	uint16 VAO, VBO, EBO;
	uint16 shader;

	uint32 indexCount = sizeof(indices) / sizeof(indices[0]);

public:

	void Init (EngineApiGetter GetEngineApi) override
	{
		// Retrieve neccessary API's

		graphics = (GraphicsApi *) GetEngineApi(EngineApi::GRAPHICS, GRAPHICS_API_VERSION);

		// Perform some other initialization

		shader = graphics -> CreateShader(vertex, fragment);

		// Vertex Array & Buffer Creation

		VAO = graphics -> CreateVertexArray();
		VBO = graphics -> CreateBuffer(VAO, vertices, 0, sizeof(vertices), attribs, 1);
		EBO = graphics -> CreateBuffer(VAO, indices, 1, sizeof(indices), nullptr, 0);
	}

	void Update (float32 delta) override
	{
		graphics -> Clear(clearColor);

		graphics -> DrawIndexed(shader, VAO, indexCount);
	}

	void Shutdown () override
	{
		graphics -> DestroyBuffer(VBO);
		graphics -> DestroyBuffer(EBO);

		graphics -> DestroyVertexArray(VAO);
	}
};

EXPORT_PLUGIN(BasicPlugin, "Basic Plugin", 1, 0);
