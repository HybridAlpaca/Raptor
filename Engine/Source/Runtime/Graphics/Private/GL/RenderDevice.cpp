#include "RenderDevice.h"
#include "RenderState.h"

#include <Display.h>

#include <iostream>

// <GL/glew.h> is included in RenderState

using namespace Graphics;

// file-local private information

namespace
{
	GL::RenderState state;
	RenderStats stats;

	// Rudimentary GPU resource system
	GLuint resourceBuffer [4096];
	uint32 resourceIndex = 0;

	void GLAPIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
	{
		/// @warning GLDebugCallback can be called from any thread; thread safety of the following statement is unknown to me :/
		++stats.APICallErrors;
		
		cchar severityStr = (severity == GL_DEBUG_SEVERITY_HIGH ? "ERR" : (severity == GL_DEBUG_SEVERITY_MEDIUM ? "WARN" : (severity == GL_DEBUG_SEVERITY_LOW ? "NOTE" : "INFO")));
		std::cout << "RenderDevice - " << severityStr << " '" << message << "'" << '\n';
	}

	// Wondering if GL_CALL is really needed...
	#define GL_CALL(stmt) do \
	{ \
		stmt; \
		++stats.APICallCount; \
	} while (0);
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
}

RenderStats RenderDevice::Stats ()
{
	return stats;
}

ResourceHandle RenderDevice::AllocateShaderProgram (cchar vertexCode, cchar fragmentCode)
{
	// Create shaders
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Set shader source code
	GL_CALL(glShaderSource(vertexShader, 1, & vertexCode, nullptr));
	GL_CALL(glShaderSource(fragmentShader, 1, & fragmentCode, nullptr));

	// Compile shaders
	GL_CALL(glCompileShader(vertexShader));
	GL_CALL(glCompileShader(fragmentShader));

	// Create shader program
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders to program
	GL_CALL(glAttachShader(shaderProgram, vertexShader));
	GL_CALL(glAttachShader(shaderProgram, fragmentShader));

	// Link shaders together inside program
	GL_CALL(glLinkProgram(shaderProgram));

	// Clean up
	GL_CALL(glDetachShader(shaderProgram, vertexShader));
	GL_CALL(glDetachShader(shaderProgram, fragmentShader));
	GL_CALL(glDeleteShader(vertexShader));
	GL_CALL(glDeleteShader(fragmentShader));

	++stats.shaderProgramCount;
	++resourceIndex;
	resourceBuffer[resourceIndex] = shaderProgram;

	return resourceIndex;
}

void RenderDevice::DestroyShaderProgram (ResourceHandle resource)
{
	--stats.shaderProgramCount;
	glDeleteProgram(resourceBuffer[resource]);
}

ResourceHandle RenderDevice::AllocateVertexArray (const VertexArrayDescription & desc)
{
	// Create handles to buffers
	GLuint VAO;
	GLuint buffers [2]; // 0 = VBO, 1 = EBO

	// Create the buffers and populate handles
	GL_CALL(glGenVertexArrays(1, & VAO));
	GL_CALL(glGenBuffers(2, buffers));

	// Bind the vertex array
	GL_CALL(glBindVertexArray(VAO));
	state.boundVAO = VAO;

	// Fill the vertex buffer
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffers[0]));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, desc.verticesSize, 0, GL_STATIC_DRAW));
	GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, desc.verticesSize, desc.vertices));

	// Fill the index buffer
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.indicesSize, 0, GL_STATIC_DRAW));
	GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, desc.indicesSize, desc.indices));

	// The current vertex layout assumes an interleaved approach to filling the buffer.  This means that of the three vertex attributes (P, N, T), the buffer will look like (PNTPNTPNTPNTPNTPNT...)
	// There are many approaches to filling the vertex buffer, and we will likely use many variations of them depending on the type of mesh being uploaded.
	for (uint32 i = 0; i < desc.bufferDescCount; ++i)
	{
		// Retrieve the buffer attribute description
		VertexAttribute & bufferDesc = desc.vertexAttributes[i];
		bufferDesc.offset = (i > 0) ? (desc.vertexAttributes[i - 1].elementCount + desc.vertexAttributes[i - 1].offset) : 0;

		// Inform OpenGL of how to read the data
		GL_CALL(glVertexAttribPointer(i, bufferDesc.elementCount, GL_FLOAT, GL_FALSE, bufferDesc.stride * sizeof(float), (void *) (bufferDesc.offset * sizeof(float))));

		// Enable the vertex attribute
		GL_CALL(glEnableVertexAttribArray(i));
	}

	++stats.vertexArrayCount;
	++resourceIndex;
	resourceBuffer[resourceIndex] = VAO;

	return resourceIndex;
}

void RenderDevice::DestroyVertexArray (ResourceHandle resource)
{
	--stats.vertexArrayCount;
	GL_CALL(glDeleteVertexArrays(1, & resourceBuffer[resource]));
}

void RenderDevice::Clear (const Commands::Clear & cmd)
{
	GL_CALL(glClearColor(cmd.r, cmd.g, cmd.b, cmd.a));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void RenderDevice::Draw (const Commands::Draw & cmd)
{
	if (state.boundProgram != resourceBuffer[cmd.shaderProgram])
	{
		// If the shader program is not bound, bind it
		GL_CALL(glUseProgram(resourceBuffer[cmd.shaderProgram]));
		state.boundProgram = resourceBuffer[cmd.shaderProgram];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;
	if (state.boundVAO != resourceBuffer[cmd.vertexArray])
	{
		// If the vertex array is not bound, bind it
		GL_CALL(glBindVertexArray(resourceBuffer[cmd.vertexArray]));
		state.boundVAO = resourceBuffer[cmd.vertexArray];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;

	GL_CALL(glDrawArrays(GL_TRIANGLES, cmd.indexOffset, cmd.indexCount));
}

void RenderDevice::DrawIndexed (const Commands::DrawIndexed & cmd)
{
	if (state.boundProgram != resourceBuffer[cmd.shaderProgram])
	{
		// If the shader program is not bound, bind it
		GL_CALL(glUseProgram(resourceBuffer[cmd.shaderProgram]));
		state.boundProgram = resourceBuffer[cmd.shaderProgram];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;
	if (state.boundVAO != resourceBuffer[cmd.vertexArray])
	{
		// If the vertex array is not bound, bind it
		GL_CALL(glBindVertexArray(resourceBuffer[cmd.vertexArray]));
		state.boundVAO = resourceBuffer[cmd.vertexArray];
		++stats.drawCacheMisses;
	}
	++stats.drawCacheAccesses;

	GL_CALL(glDrawElements(GL_TRIANGLES, cmd.indexCount, GL_UNSIGNED_INT, (void *) cmd.indexOffset));
}

void RenderDevice::Present (const Display & display)
{
	// Reset statistics
	stats.APICallCount = 0;
	stats.APICallErrors = 0;
	stats.drawCacheAccesses = 0;
	stats.drawCacheMisses = 0;

	// Forward the Present command
	display.SwapBuffers();
}

void RenderDevice::Resize (uint32 width, uint32 height)
{
	stats.width = width;
	stats.height = height;

	// Don't cache the size, since Resize should only occur after an actual resize
	GL_CALL(glViewport(0, 0, width, height));
}
