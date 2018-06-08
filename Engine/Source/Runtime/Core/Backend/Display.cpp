#include <Core/Common/Required.h>
#include "Display.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using Core::Backend::DisplayConfig;
using Core::Backend::Display;

/*
 *
 * name: Display::Display
 * @param uint16 width, height; cchar title
 *
 * Creates a GLFW window object based off of
 * aplication config data.
 *
 */

Display::Display (const DisplayConfig & config)
{
	if (!glfwInit())
	{
		FATAL("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		config.width,
		config.height,
		config.title,
		nullptr,
		nullptr
	);

	BindContext();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// OpenGL extensions couldn't be loaded
		DEBUG("GLEW failed to initialize");
	}
}

/*
 *
 * name: Display::~Display
 *
 * Destroys the internal GFLW window.
 *
 */
Display::~Display ()
{
	running = false;
	glfwDestroyWindow(window);
}

/*
 *
 * name: Display::Clear
 * @param float r, g, b, a
 * @return void
 *
 * Used to clear any opengl buffers during
 * rendering.
 *
 */

void Display::Clear (float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::BindContext ()
{
	glfwMakeContextCurrent(window);
}

void Display::ProcessInput ()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*
 *
 * name: Display::Update
 * @param void
 * @return void
 *
 * Updates the display, to be called after
 * any other draw operations are performed.
 *
 */
void Display::Update ()
{
	glfwPollEvents();
	ProcessInput();
	if (glfwWindowShouldClose(window)) running = false;
	glfwSwapBuffers(window);
}





