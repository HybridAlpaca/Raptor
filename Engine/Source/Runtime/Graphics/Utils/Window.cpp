#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Common/Required.h>
#include "Window.h"

using Graphics::Utils::WindowController;

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
		Destroy();
		FATAL("Window creation failed");
		return;
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Destroy();
		FATAL("Unable to load OpenGL extensions");
		return;
	}
	
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, FBResizeCallback);
	
}

WindowController::~WindowController ()
{
	Destroy();
}

void WindowController::Destroy ()
{
	shouldClose =  true;
	glfwTerminate();
}

void WindowController::FBResizeCallback (GLFWwindow * window, int16 width, int16 height)
{
	glViewport(0, 0, width, height);
}

void WindowController::ProcessInput ()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// escape key has been pressed
		glfwSetWindowShouldClose(window, true);
	}
}

void WindowController::Update ()
{
	ProcessInput();
	
	glfwSwapBuffers(window);
	glfwPollEvents();
	shouldClose = glfwWindowShouldClose(window);
}