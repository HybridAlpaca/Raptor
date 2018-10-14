#include <Window.h>

#include <GLFW/glfw3.h>

using namespace Graphics;

Window::Window (const WindowDescriptor & desc)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSwapInterval(1);
	window = glfwCreateWindow(desc.width, desc.height, desc.title, nullptr, nullptr);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::BindContext () const
{
	glfwMakeContextCurrent(window);
}

void Window::PollEvents () const
{
	glfwPollEvents();
}

void Window::SwapBuffers () const
{
	glfwSwapBuffers(window);
}

bool Window::ShouldClose () const
{
	return glfwWindowShouldClose(window);
}
