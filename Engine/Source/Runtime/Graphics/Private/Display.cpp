#include <Display.h>

#include <GLFW/glfw3.h>

namespace
{
	const uint16 MAX_WINDOWS = 65535;

	GLFWwindow * windowBuffer [MAX_WINDOWS] { nullptr };

	uint16 windowIndex = 0;
	uint16 windowCount = 0;
}

namespace Graphics::Display
{
	void Init ()
	{
		glfwInit();
	}

	Window::Window (const WindowDescriptor & desc)
	: handle (++windowIndex)
	{
		if (!windowCount)
		{
			glfwInit();
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		windowBuffer[handle] = glfwCreateWindow(desc.width, desc.height, desc.title, nullptr, nullptr);

		glfwMakeContextCurrent(windowBuffer[handle]);

		++windowCount;
	}

	Window::~Window ()
	{
		glfwDestroyWindow(windowBuffer[handle]);

		--windowCount;

		if (!windowCount)
		{
			glfwTerminate();
		}
	}

	void Window::PollEvents () const
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers () const
	{
		glfwSwapBuffers(windowBuffer[handle]);
	}

	uint32 Window::FrameWidth () const
	{
		int32 width;
		glfwGetFramebufferSize(windowBuffer[handle], & width, nullptr);

		return width;
	}

	uint32 Window::FrameHeight () const
	{
		int32 height;
		glfwGetFramebufferSize(windowBuffer[handle], nullptr, & height);

		return height;
	}

	bool Window::ShouldClose () const
	{
		return glfwWindowShouldClose(windowBuffer[handle]);
	}

	void Window::ShouldClose (bool value) const
	{
		glfwSetWindowShouldClose(windowBuffer[handle], value);
	}
}
