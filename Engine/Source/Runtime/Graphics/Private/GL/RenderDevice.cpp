#include <RenderDevice.h>

#include <GL/glew.h>

namespace
{
	const uint16 MAX_RENDER_RESOURCES = 65535;

	GLuint resourceBuffer [MAX_RENDER_RESOURCES];

	uint16 resourceIndex = 0;
}

namespace Graphics::RenderDevice
{
	void Init ()
	{
		glewExperimental = true;
		glewInit();
	}

	void Clear (float32 r, float32 g, float32 b, float32 a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	RenderResource CreateShader (cchar code, ShaderType type)
	{
		GLuint shader = glCreateShader((type == ShaderType::VERTEX) ? (GL_VERTEX_SHADER) : (GL_FRAGMENT_SHADER));

		glShaderSource(shader, 1, & code, nullptr);

		glCompileShader(shader);

		resourceBuffer[++resourceIndex] = shader;
		return resourceIndex;
	}

	RenderResource CreateProgram (const RenderResource * shaders, uint16 shaderCount)
	{
		GLuint shaderProgram = glCreateProgram();

		// Attach shaders to program
		for (uint32 i = 0; i < shaderCount; ++i)
		{
			glAttachShader(shaderProgram, resourceBuffer[shaders[i]]);
		}

		// Link shaders together inside program
		glLinkProgram(shaderProgram);

		// Clean up
		for (uint32 i = 0; i < shaderCount; ++i)
		{
			glDetachShader(shaderProgram, resourceBuffer[shaders[i]]);
		}

		resourceBuffer[++resourceIndex] = shaderProgram;
		return resourceIndex;
	}

	RenderResource CreateVertexArray ()
	{
		GLuint vertexArray;
		glGenVertexArrays(1, & vertexArray);

		resourceBuffer[++resourceIndex] = vertexArray;
		return resourceIndex;
	}

	RenderResource CreateBuffer (RenderResource vertexArray, void * data, const BufferDescriptor & desc)
	{
		GLuint buffer;
		glGenBuffers(1, & buffer);

		glBindVertexArray(resourceBuffer[vertexArray]);

		GLenum bufferType = (desc.type == BufferType::VERTEX) ? (GL_ARRAY_BUFFER) : (GL_ELEMENT_ARRAY_BUFFER);

		glBindBuffer(bufferType, buffer);
		glBufferData(bufferType, desc.size, data, GL_STATIC_DRAW);

		resourceBuffer[++resourceIndex] = buffer;
		return resourceIndex;
	}
}
