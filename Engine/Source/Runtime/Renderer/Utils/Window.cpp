#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Misc/CoreTypes.h>

#include "Window.h"

Window::Window (uint16 width, uint16 height, const char * title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
	
	if (window == nullptr)
	{
		// GLFW was unable to open the window
		// Possible OS failure?
	
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(window);
	
	glewExperimental = true; // tell Glew to use core profile
	
	if (glewInit() != GLEW_OK)
	{
		// Glew was unable to load the OpenGL
		// extensions.
	
		glfwTerminate();
		return;
	}
}

Window::~Window ()
{
	Close();
}

void Window::Close ()
{
	glfwMakeContextCurrent(window);
	glfwTerminate();
}

void Window::Update ()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::shouldClose ()
{
	return glfwWindowShouldClose(window);
}