#include <Display.h>

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Graphics;

// File-local internal data

namespace
{
	uint16 windowCount = 0;
	GLFWwindow * windowBuffer [Display::MAX_WINDOWS] { nullptr };
}

Display::WindowHandle Display::Create (const InitDescriptor & desc)
{
	if (!glfwInit())
	{
		/// @todo Log error
		return NULL_HANDLE;
	}

	// OpenGL specific window hints

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, desc.glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, desc.glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow * window = glfwCreateWindow(desc.width, desc.height, desc.title, nullptr, nullptr);

	if (window == nullptr)
	{
		/// @todo Log error
		return NULL_HANDLE;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(desc.vsync);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Setup style
	ImGui::StyleColorsDark();

	windowBuffer[++windowCount] = window;
	return windowCount;
}

void Display::Destroy (WindowHandle window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(windowBuffer[window]);
	windowBuffer[window] = nullptr;

	glfwTerminate();
}

bool Display::Closed (WindowHandle window)
{
	return glfwWindowShouldClose(windowBuffer[window]);
}

void Display::Close (WindowHandle window)
{
	glfwSetWindowShouldClose(windowBuffer[window], true);
}

void Display::PollEvents ()
{
	glfwPollEvents();
}

void Display::SwapBuffers (WindowHandle window)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(windowBuffer[window]);
}

uint32 Display::FrameWidth (WindowHandle window)
{
	int32 width, height;

	glfwGetFramebufferSize(windowBuffer[window], & width, & height);

	return width;
}

uint32 Display::FrameHeight (WindowHandle window)
{
	int32 width, height;

	glfwGetFramebufferSize(windowBuffer[window], & width, & height);

	return height;
}
