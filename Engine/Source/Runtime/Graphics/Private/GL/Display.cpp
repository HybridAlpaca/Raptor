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
	glfwSwapInterval(params.vsync);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

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
