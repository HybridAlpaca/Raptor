#include <Core/Common/Required.h>
#include "Display.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using Core::Backend::DisplayConfig;
using Core::Backend::Display;

/*
 *
 * name: Display::Display
 * @param DisplayConfig config
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		config.width,
		config.height,
		config.title,
		nullptr,
		nullptr
	);

	// glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	BindContext();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		// OpenGL extensions couldn't be loaded
		DEBUG("GLEW failed to initialize");
	}

	DEBUG("Created display");
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
	DEBUG("Destroyed display");
}

/*
 *
 * name: Display::Clear
 * @param float r, g, b, a
 * @return void
 *
 * Used to clear any OpenGL buffers during
 * rendering.
 *
 */

void Display::BindContext ()
{
	glfwMakeContextCurrent(window);
}

const bool Display::GetKey (int32 key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

/*
 *
 * name: Display::Update
 * @return void
 *
 * Updates the display, to be called after
 * any other draw operations are performed.
 *
 */

void Display::Update ()
{
	glfwPollEvents();
	if (glfwWindowShouldClose(window)) running = false;

	glfwSwapBuffers(window);
}





