#include "RenderDevice.h"
#include "RenderState.h"

#include <Display.h>

#include <iostream>

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

		std::cerr << "RenderDevice - " << GLEnumToString(type) << " '" << message << "'\n";
	}
}

// Backend code

void RenderDevice::Initialize (const InitDescriptor & desc)
{
	glewExperimental = GL_TRUE;
	glewInit();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Sometimes GLEW Experimental Initialization causes unknown errors at runtime, perhaps due to unsupported driver features
	}

	if (desc.debug)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GLDebugCallback, nullptr);
	}

	glGetIntegerv(GL_MAJOR_VERSION, & stats.contextVersionMajor);
	glGetIntegerv(GL_MINOR_VERSION, & stats.contextVersionMinor);

	stats.vendor = glGetString(GL_VENDOR);
	stats.rendererName = glGetString(GL_RENDERER);
	stats.deviceName = "OpenGL Core";
}

RenderDevice::GraphicsBackend RenderDevice::BackendType ()
{
	return GraphicsBackend::OPENGL_CORE;
}

RenderStats RenderDevice::Stats ()
{
	return stats;
}

RenderResource RenderDevice::AllocateShader (cchar code, ShaderType type)
{
	GLuint shader = glCreateShader((type == ShaderType::VERTEX) ? (GL_VERTEX_SHADER) : (GL_FRAGMENT_SHADER));
	glShaderSource(shader, 1, & code, nullptr);

	glCompileShader(shader);

	++resourceIndex;
	resourceBuffer[resourceIndex] = shader;

	return { resourceIndex, 0 };
}

void RenderDevice::DestroyShader (RenderResource & resource)
{
	resource.Invalidate();
	glDeleteShader(resourceBuffer[resource]);
}

RenderResource RenderDevice::AllocateShaderProgram (const RenderResource * const shaders, uint32 shaderCount)
{
	// Create shader program
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

	++resourceIndex;
	resourceBuffer[resourceIndex] = shaderProgram;

	return { resourceIndex, 0 };
}

void RenderDevice::DestroyShaderProgram (RenderResource resource)
{
	glDeleteProgram(resourceBuffer[resource]);
}

RenderResource RenderDevice::AllocateVertexArray ()
{
	// Create handles to buffers
	GLuint VAO;

	// Create the buffers and populate handles
	glGenVertexArrays(1, & VAO);

	++resourceIndex;
	resourceBuffer[resourceIndex] = VAO;

	return {resourceIndex, 0};
}

void RenderDevice::DestroyVertexArray (RenderResource & resource)
{
	resource.Invalidate();
	glDeleteVertexArrays(1, & resourceBuffer[resource]);
}

RenderResource RenderDevice::AllocateBuffer (RenderResource vertexArray, const void * data, const BufferDescriptor & desc)
{
	GLuint buf;
	glGenBuffers(1, & buf);

	state.BindVAO(resourceBuffer[vertexArray]);

	GLenum bufferType = (desc.type == BufferType::VERTEX) ? (GL_ARRAY_BUFFER) : (GL_ELEMENT_ARRAY_BUFFER);

	glBindBuffer(bufferType, buf);
	glBufferData(bufferType, desc.size, (void *) 0, GL_STATIC_DRAW);
	glBufferSubData(bufferType, 0, desc.size, data);

	switch (desc.type)
	{
		// For vertex buffers, describe vertex attributes
		case BufferType::VERTEX:
			for (uint32 i = 0; i < desc.format.attributeCount; ++i)
			{
				// Retrieve the buffer attribute description
				const VertexAttribute & attrib = desc.format.attributes[i];

				// Inform OpenGL of how to read the data
				/// @warning This assumes all vertex data is 32 bits wide.
				/// @todo Provide a more type-safe stride / offset deduction mechanism
				glVertexAttribPointer(i, attrib.size, GL_FLOAT, GL_FALSE, attrib.stride * sizeof(float32), (GLvoid *) (attrib.offset * sizeof(float32)));

				// Enable the vertex attribute
				glEnableVertexAttribArray(i);
			}
			break;

		// Don't do anything for index buffers
		case BufferType::INDEX:
		default:
			break;
	}

	++resourceIndex;
	resourceBuffer[resourceIndex] = buf;

	return {resourceIndex, 0};
}

void RenderDevice::DestroyBuffer (RenderResource & resource)
{
	resource.Invalidate();
	glDeleteBuffers(1, & resourceBuffer[resource]);
}

void RenderDevice::Clear (float color [4])
{
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderDevice::ShaderUniform (RenderResource program, cchar name, float32 value)
{
	state.BindProgram(resourceBuffer[program]);

	GLuint location = glGetUniformLocation(resourceBuffer[program], name);
	glUniform1f(location, value);
}

void RenderDevice::ShaderUniform (RenderResource program, cchar name, float32 values [3])
{
	state.BindProgram(resourceBuffer[program]);

	GLuint location = glGetUniformLocation(resourceBuffer[program], name);
	glUniform3f(location, values[0], values[1], values[2]);
}

void RenderDevice::Draw (RenderResource program, RenderResource vertexArray, uint32 indexCount, uint32 indexOffset)
{
	state.BindProgram(resourceBuffer[program]);
	state.BindVAO(resourceBuffer[vertexArray]);

	glDrawArrays(GL_TRIANGLES, indexOffset, indexCount);
}

void RenderDevice::DrawIndexed (RenderResource program, RenderResource vertexArray, uint32 indexCount, uint32 indexOffset)
{
	state.BindProgram(resourceBuffer[program]);
	state.BindVAO(resourceBuffer[vertexArray]);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (GLvoid *) indexOffset);
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
