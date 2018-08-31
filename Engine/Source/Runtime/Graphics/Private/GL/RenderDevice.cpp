#include "RenderDevice.h"
#include "RenderState.h"

#include <Display.h>

// <GL/glew.h> is included in RenderState

using namespace Graphics;

namespace
{
	// file-local private information

	GL::RenderState state;

	GLuint shaderPrograms [4096];
	uint32 shaderIndex = 0;
}

void Backend::Init ()
{
	glewExperimental = GL_TRUE;
	glewInit();
}

uint32 Backend::AllocateShaderProgram (cchar vertexCode, cchar fragmentCode)
{
	// Create shaders
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Set shader source code
	glShaderSource(vertexShader, 1, & vertexCode, nullptr);
	glShaderSource(fragmentShader, 1, & fragmentCode, nullptr);

	// Compile shaders
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	/// @todo Check compilation status

	// Create shader program
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link shaders together inside program
	glLinkProgram(shaderProgram);

	/// @todo Check linking status

	// Clean up
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	++shaderIndex;
	shaderPrograms[shaderIndex] = shaderProgram;

	return shaderIndex;
}

void Backend::DestroyShaderProgram (uint32 program)
{
	glDeleteProgram(shaderPrograms[program]);
}

void Backend::Clear (float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Backend::Present (const Display & display)
{
	display.SwapBuffers();
}

void Backend::Resize (uint32 width, uint32 height)
{
	/// @todo cache resolution to avoid uneccessary draw calls
	glViewport(0, 0, width, height);
}
