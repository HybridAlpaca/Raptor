#include "Display.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Display::Display ()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Lorum Ipsum", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
		glfwTerminate();
		return;
	}

  glViewport(0, 0, 640, 480);
  glfwSetFramebufferSizeCallback(window, FBSizeCallback);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}

Display::~Display ()
{
	glfwTerminate();
}

void Display::FBSizeCallback (GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Display::Update () const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Display::ShouldClose () const
{
	return glfwWindowShouldClose(window);
}
