#include <Core/Common/Required.h>
#include "Display.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using Graphics::Device::Display;

Display::Display (uint16 width, uint16 height, cchar title)
{
	glfwInit();
	
	// context hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // buffer hints
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	
	window = glfwCreateWindow(
		width,
		height,
		title,
		nullptr,
		nullptr
	);
	
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		DEBUG("GLEW failed to initialize");
	}
}

Display::~Display ()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
	glfwTerminate();
}

void Display::Clear (float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update ()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
	closed = glfwWindowShouldClose(window);
}