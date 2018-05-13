#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include <Core/Misc/Required.h>

using Renderer::Utils::WindowController;

///
/// static methods
///

void WindowController::FBResizeCallback (GLFWwindow * window, uint16 width, uint16 height)
{
	glViewport(0, 0, width, height);
}

///
/// c'tors and d'tors
///

WindowController::WindowController (uint16 width, uint16 height, cchar title)
: shouldClose(false)
{
	glfwInit();
	
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr)
	{
		DEBUG("window creation failed");
		Destroy();
		return;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		DEBUG("unable to load OpenGL extensions");
		Destroy();
		return;
	}
	
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, FBResizeCallback);
	
}

WindowController::~WindowController ()
{
	Destroy();
}

///
/// methods
///

void WindowController::Destroy ()
{
	glfwTerminate();
}

void WindowController::Update ()
{
	shouldClose = glfwWindowShouldClose(window);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}