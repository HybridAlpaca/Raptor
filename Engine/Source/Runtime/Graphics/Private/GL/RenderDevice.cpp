#include "RenderDevice.h"
#include "RenderState.h"

#include <Display.h>

#include <iostream>

// <GL/glew.h> is included in RenderState

using namespace Graphics;

namespace
{
	// file-local private information

	GL::RenderState state;

	GLuint resourceBuffer [4096];
	uint32 resourceIndex = 0;

	void GLErrorCheck (cchar stmt, cchar fname, uint32 line)
	{
		GLenum err;
		cchar text;

		while ((err = glGetError()) != GL_NO_ERROR)
		{
			switch (err)
			{
				case GL_INVALID_OPERATION: text = "INVALID_OPERATION"; break;
				case GL_INVALID_ENUM: text = "INVALID_ENUM"; break;
				case GL_INVALID_VALUE: text = "INVALID_VALUE"; break;
				case GL_OUT_OF_MEMORY: text = "OUT_OF_MEMORY"; break;
				case GL_INVALID_FRAMEBUFFER_OPERATION: text = "INVALID_FRAMEBUFFER_OPERATION"; break;
			}
			std::cerr << "GL::" << text << " - " << stmt << " (" << fname << ", " << line << ")" << '\n';
		}
	}

	#define GL_CALL(stmt) do \
	{ \
		stmt; \
		GLErrorCheck(#stmt, __FILE__, __LINE__); \
	} while (0);
}

void Backend::Init ()
{
	glewExperimental = GL_TRUE;
	glewInit();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Sometimes GLEW Experimental Initialization causes unknown errors at runtime, perhaps due to unsupported driver features
	}
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

	// Check compilation status
	GLint success;
	char infoLog [512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, & success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERR::SHADER " << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, & success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERR::SHADER " << infoLog << std::endl;
	}

	// Create shader program
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders to program
	GL_CALL(glAttachShader(shaderProgram, vertexShader));
	GL_CALL(glAttachShader(shaderProgram, fragmentShader));

	// Link shaders together inside program
	GL_CALL(glLinkProgram(shaderProgram));

	// Check linking status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, & success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM " << infoLog << std::endl;
	}

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

ResourceHandle Backend::AllocateVertexArray (float * vertices)
{
	GLuint VAO;
	GLuint VBO;

	GL_CALL(glGenVertexArrays(1, & VAO));
	GL_CALL(glGenBuffers(1, & VBO));

	GL_CALL(glBindVertexArray(VAO));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0));
	GL_CALL(glEnableVertexAttribArray(0));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CALL(glBindVertexArray(0));

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
	GL_CALL(glUseProgram(resourceBuffer[shader]));
	GL_CALL(glBindVertexArray(resourceBuffer[vertexArray]));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, indexCount));
}

void Backend::Present (const Display & display)
{
	display.SwapBuffers();
}

void Backend::Resize (uint32 width, uint32 height)
{
	/// @todo cache resolution to avoid uneccessary draw calls
	GL_CALL(glViewport(0, 0, width, height));
}
