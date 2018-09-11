#include <Display.h>

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Graphics;

Display::Display (const DisplayParams & params)
{
	if (!glfwInit())
	{
		return;
	}

	GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode * mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode -> redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode -> greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode -> blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode -> refreshRate);

	// OpenGL specific window hints

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, params.glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, params.glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	uint32 width  = (params.width)  ? (params.width)  : (mode -> width);
	uint32 height = (params.height) ? (params.height) : (mode -> height);

	window = glfwCreateWindow(width, height, params.title, (params.fullscreen ? monitor : nullptr), nullptr);

	if (window == nullptr)
	{
		/// @todo Log error
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(params.vsync);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	// Setup style
	ImGui::StyleColorsDark();
}

Display::~Display ()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	window = nullptr;

	glfwTerminate();
}

bool Display::Closed () const
{
	return glfwWindowShouldClose(window);
}

void Display::Close () const
{
	glfwSetWindowShouldClose(window, true);
}

void Display::PollEvents () const
{
	glfwPollEvents();
}

void Display::SwapBuffers () const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}

double Display::Time () const
{
	return glfwGetTime();
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
