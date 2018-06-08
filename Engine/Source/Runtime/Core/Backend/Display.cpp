#include <Core/Common/Required.h>
#include "Application.h"
#include "Display.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using Core::Backend::Application;
using Core::Backend::Display;

/*
 * 
 * name: Display::Display
 * @param uint16 width, height; cchar title
 * 
 * Handles creation of SDL window and OpenGL
 * context.
 * 
 */

Display::Display (Application & app)
: app(app)
{
	window = glfwCreateWindow(
		app.Config().width,
		app.Config().height,
		app.Config().title,
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
 * Destroys the OpenGL context and the SDL window,
 * in that order.
 * 
 */
Display::~Display ()
{
	app.Running(false);
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
	if (glfwWindowShouldClose(window)) app.Running(false);
	glfwSwapBuffers(window);
}





