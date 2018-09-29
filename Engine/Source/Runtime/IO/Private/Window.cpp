#include <Window.h>

#include <GLFW/glfw3.h>

#include <iostream>

using namespace IO;

Window::Window ()
{
	glfwInit();

	std::cout << "[IO] Creating window" << '\n';

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Hello, Kernel!", nullptr, nullptr);
}

Window::~Window ()
{
	std::cout << "[IO] Destroying window" << '\n';

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::PollEvents ()
{
	glfwPollEvents();
}

void Window::SwapBuffers ()
{
	glfwSwapBuffers(window);
}

bool Window::ShouldClose () const
{
	return glfwWindowShouldClose(window);
}
