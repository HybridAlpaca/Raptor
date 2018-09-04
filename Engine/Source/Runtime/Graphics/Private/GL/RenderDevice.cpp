#include "RenderDevice.h"
#include "RenderState.h"

#include <Display.h>
#include <Raptor/Console.h>

using namespace Graphics;

// file-local private information

namespace
{
	GL::RenderState state;
	RenderStats stats;

	// Rudimentary GPU resource system
	GLuint resourceBuffer [4096];
	uint16 resourceIndex = 0;

	cchar GLEnumToString (GLenum glEnum)
	{
		switch (glEnum)
		{
			case GL_DEBUG_TYPE_ERROR:
				return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "DEPRECATED";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "UNDEFINED BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER:
				return "MARKER";
			case GL_DEBUG_SEVERITY_HIGH:
				return "CRITICAL";
			case GL_DEBUG_SEVERITY_MEDIUM:
				return "ERROR";
			case GL_DEBUG_SEVERITY_LOW:
				return "NOTE";
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				return "INFO";
			default:
				return "UNKNOWN";
		}
	}

	void GLAPIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
	{
		/// @warning GLDebugCallback can be called from any thread; thread safety of the following statement is unknown to me :/
		++stats.APICallErrors;

		Raptor::Print("RenderDevice - ");
		Raptor::Print(GLEnumToString(type));
		Raptor::Print(" '");
		Raptor::Print(message);
		Raptor::Println("'");
	}
}

// Backend code

void RenderDevice::Initialize ()
{
	glewExperimental = GL_TRUE;
	glewInit();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Sometimes GLEW Experimental Initialization causes unknown errors at runtime, perhaps due to unsupported driver features
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLDebugCallback, nullptr);

	glGetIntegerv(GL_MAJOR_VERSION, & stats.contextVersionMajor);
	glGetIntegerv(GL_MINOR_VERSION, & stats.contextVersionMinor);

	stats.vendor = glGetString(GL_VENDOR);
	stats.rendererName = glGetString(GL_RENDERER);
	stats.deviceName = "OpenGL Core";
}

RenderStats RenderDevice::Stats ()
{
	return stats;
}

RenderResource RenderDevice::AllocateShaderProgram (cchar vertexCode, cchar fragmentCode)
{
	// Create shaders
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Set shader source code
	glShaderSource(vertexShader, 1, & vertexCode, nullptr);
	// glShaderSource(vertexShader, 1, & vertexCode, nullptr));
	glShaderSource(fragmentShader, 1, & fragmentCode, nullptr);

	// Compile shaders
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Create shader program
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link shaders together inside program
	glLinkProgram(shaderProgram);

	// Clean up
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	++stats.resourceCalls;
	++resourceIndex;
	resourceBuffer[resourceIndex] = shaderProgram;

	return {resourceIndex, 0};
}

void RenderDevice::DestroyShaderProgram (RenderResource resource)
{
	++stats.resourceCalls;
	glDeleteProgram(resourceBuffer[resource]);
}

RenderResource RenderDevice::AllocateVertexArray (const VertexArrayDescription & desc)
{
	// Create handles to buffers
	GLuint VAO;
	GLuint buffers [2]; // 0 = VBO, 1 = EBO

	// Create the buffers and populate handles
	glGenVertexArrays(1, & VAO);
	glGenBuffers(2, buffers);

	// Bind the vertex array
	glBindVertexArray(VAO);
	state.boundVAO = VAO;

	// Fill the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, desc.verticesSize, (void *) 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, desc.verticesSize, desc.vertices);

	// Fill the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.indicesSize, (void *) 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, desc.indicesSize, desc.indices);

	// The current vertex layout assumes an interleaved approach to filling the buffer.  This means that of the three vertex attributes (P, N, T), the buffer will look like (PNTPNTPNTPNTPNTPNT...)
	// There are many approaches to filling the vertex buffer, and we will likely use many variations of them depending on the type of mesh being uploaded.
	for (uint32 i = 0; i < desc.bufferDescCount; ++i)
	{
		// Retrieve the buffer attribute description
		VertexAttribute & bufferDesc = desc.vertexAttributes[i];
		bufferDesc.offset = (i > 0) ? (desc.vertexAttributes[i - 1].elementCount + desc.vertexAttributes[i - 1].offset) : 0;

		// Inform OpenGL of how to read the data
		glVertexAttribPointer(i, bufferDesc.elementCount, GL_FLOAT, GL_FALSE, bufferDesc.stride * sizeof(float), (GLvoid *) (bufferDesc.offset * sizeof(float)));

		// Enable the vertex attribute
		glEnableVertexAttribArray(i);
	}

	++stats.resourceCalls;
	++resourceIndex;
	resourceBuffer[resourceIndex] = VAO;

	return {resourceIndex, 0};
}

void RenderDevice::DestroyVertexArray (RenderResource resource)
{
	++stats.resourceCalls;

	glDeleteVertexArrays(1, & resourceBuffer[resource]);
}

void RenderDevice::Clear (const Commands::Clear & cmd)
{
	++stats.drawCalls;

	glClearColor(cmd.r, cmd.g, cmd.b, cmd.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderDevice::Draw (const Commands::Draw & cmd)
{
	if (state.boundProgram != resourceBuffer[cmd.shaderProgram])
	{
		// If the shader program is not bound, bind it
		glUseProgram(resourceBuffer[cmd.shaderProgram]);
		state.boundProgram = resourceBuffer[cmd.shaderProgram];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;
	if (state.boundVAO != resourceBuffer[cmd.vertexArray])
	{
		// If the vertex array is not bound, bind it
		glBindVertexArray(resourceBuffer[cmd.vertexArray]);
		state.boundVAO = resourceBuffer[cmd.vertexArray];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;
	++stats.drawCalls;

	glDrawArrays(GL_TRIANGLES, cmd.indexOffset, cmd.indexCount);
}

void RenderDevice::DrawIndexed (const Commands::DrawIndexed & cmd)
{
	if (state.boundProgram != resourceBuffer[cmd.shaderProgram])
	{
		// If the shader program is not bound, bind it
		glUseProgram(resourceBuffer[cmd.shaderProgram]);
		state.boundProgram = resourceBuffer[cmd.shaderProgram];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;
	if (state.boundVAO != resourceBuffer[cmd.vertexArray])
	{
		// If the vertex array is not bound, bind it
		glBindVertexArray(resourceBuffer[cmd.vertexArray]);
		state.boundVAO = resourceBuffer[cmd.vertexArray];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;
	++stats.drawCalls;

	glDrawElements(GL_TRIANGLES, cmd.indexCount, GL_UNSIGNED_INT, (GLvoid *) cmd.indexOffset);
}

void RenderDevice::Present (const Display & display)
{
	// Reset statistics
	stats.drawCalls = 0;
	stats.resourceCalls = 0;
	stats.APICallErrors = 0;
	stats.drawCacheAccesses = 0;
	stats.drawCacheMisses = 0;

	// Forward the Present command
	display.SwapBuffers();
}

void RenderDevice::Resize (uint32 width, uint32 height)
{
	// Don't cache the size, since Resize should only occur after an actual resize
	glViewport(0, 0, width, height);
}
