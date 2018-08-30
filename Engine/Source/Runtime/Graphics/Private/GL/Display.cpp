#include <Display.h>

#include <GLFW/glfw3.h>

using namespace Graphics;

Display::Display (const DisplayParams & params)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, params.glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, params.glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(params.width, params.height, params.title, nullptr, nullptr);

	if (window == nullptr)
	{
		/// @todo Log error
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
}

Display::~Display ()
{
	glfwDestroyWindow(window);
	window = nullptr;

	glfwTerminate();
}

bool Display::Closed () const
{
	return glfwWindowShouldClose(window);
}

void Display::PollEvents () const
{
	glfwPollEvents();
}

void Display::SwapBuffers () const
{
	glfwSwapBuffers(window);
}

uint32 Display::FrameWidth () const
{
	int width, height;
	glfwGetFramebufferSize(window, & width, & height);
	return width;
}

uint32 Display::FrameHeight () const
{
	int width, height;
	glfwGetFramebufferSize(window, & width, & height);
	return height;
}
