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
	FrameStats frameStats;

	GLuint resourceBuffer [4096];
	uint32 resourceIndex = 0;

	void GLErrorCheck (cchar stmt, cchar fname, uint32 line)
	{
		GLenum err;
		cchar text;

		while ((err = glGetError()) != GL_NO_ERROR)
		{
			++frameStats.APICallErrors;

			switch (err)
			{
				case GL_INVALID_OPERATION:
					text = "INVALID_OPERATION";
					break;
				case GL_INVALID_ENUM:
					text = "INVALID_ENUM";
					break;
				case GL_INVALID_VALUE:
					text = "INVALID_VALUE";
					break;
				case GL_OUT_OF_MEMORY:
					text = "OUT_OF_MEMORY";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					text = "INVALID_FRAMEBUFFER_OPERATION";
					break;
				default:
					text = "UNKNOWN_ERROR";
					break;
			}

			std::cerr << "GL::" << text << " - " << stmt << " (" << fname << ", " << line << ")" << '\n';
		}
	}

	#define GL_CALL(stmt) do \
	{ \
		stmt; \
		++frameStats.APICallCount; \
		GLErrorCheck(#stmt, __FILE__, __LINE__); \
	} while (0);
}

// Backend code

void Backend::Initialize ()
{
	glewExperimental = GL_TRUE;
	glewInit();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Sometimes GLEW Experimental Initialization causes unknown errors at runtime, perhaps due to unsupported driver features
	}
}

FrameStats Backend::CurrentFrameStats ()
{
	FrameStats temp = frameStats;

	// Now that we've returned the current stats, we can reset them
	frameStats.Reset();

	return temp;
}

ResourceHandle Backend::AllocateShaderProgram (cchar vertexCode, cchar fragmentCode)
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

	++resourceIndex;
	resourceBuffer[resourceIndex] = shaderProgram;

	return resourceIndex;
}

void Backend::DestroyShaderProgram (ResourceHandle resource)
{
	glDeleteProgram(resourceBuffer[resource]);
}

ResourceHandle Backend::AllocateVertexArray (const VertexArrayDescription & desc)
{
	// Create handles to buffers
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	// Create the buffers and populate handles
	GL_CALL(glGenVertexArrays(1, & VAO));
	/// @todo Combine these two calls
	GL_CALL(glGenBuffers(1, & VBO));
	GL_CALL(glGenBuffers(1, & EBO));

	// Bind the vertex array
	GL_CALL(glBindVertexArray(VAO));
	state.boundVAO = VAO;

	// Fill the vertex buffer
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, desc.verticesSize, desc.vertices, GL_STATIC_DRAW));

	// Fill the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.indicesSize, desc.indices, GL_STATIC_DRAW);

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

	++resourceIndex;
	resourceBuffer[resourceIndex] = VAO;

	return resourceIndex;
}

void Backend::DestroyVertexArray (ResourceHandle resource)
{
	GL_CALL(glDeleteVertexArrays(1, & resourceBuffer[resource]));
}

void Backend::Clear (float r, float g, float b, float a)
{
	GL_CALL(glClearColor(r, g, b, a));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Backend::Draw (ResourceHandle shader, ResourceHandle vertexArray, uint32 indexCount)
{
	if (state.boundProgram != resourceBuffer[shader])
	{
		// If the shader program is not bound, bind it
		GL_CALL(glUseProgram(resourceBuffer[shader]));
		state.boundProgram = resourceBuffer[shader];
		++frameStats.drawCacheMisses;
	}
	++frameStats.drawCacheAccesses;
	if (state.boundVAO != resourceBuffer[vertexArray])
	{
		// If the vertex array is not bound, bind it
		GL_CALL(glBindVertexArray(resourceBuffer[vertexArray]));
		state.boundVAO = resourceBuffer[vertexArray];
		++frameStats.drawCacheMisses;
	}
	++frameStats.drawCacheAccesses;

	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, indexCount));
}

void Backend::DrawIndexed (ResourceHandle shader, ResourceHandle vertexArray, uint32 indexCount)
{
	if (state.boundProgram != resourceBuffer[shader])
	{
		// If the shader program is not bound, bind it
		GL_CALL(glUseProgram(resourceBuffer[shader]));
		state.boundProgram = resourceBuffer[shader];
		++frameStats.drawCacheMisses;
	}
	++frameStats.drawCacheAccesses;
	if (state.boundVAO != resourceBuffer[vertexArray])
	{
		// If the vertex array is not bound, bind it
		GL_CALL(glBindVertexArray(resourceBuffer[vertexArray]));
		state.boundVAO = resourceBuffer[vertexArray];
		++frameStats.drawCacheMisses;
	}
	++frameStats.drawCacheAccesses;

	GL_CALL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0));
}

void Backend::Present (const Display & display)
{
	// Forward the Present command
	display.SwapBuffers();
}

void Backend::Resize (uint32 width, uint32 height)
{
	// Cache the internal device resolution to avoid uneccessary draw calls
	if ((width != state.internalWidth) && (height != state.internalHeight))
	{
		state.internalWidth = width;
		state.internalHeight = height;

		GL_CALL(glViewport(0, 0, width, height));
	}
}
