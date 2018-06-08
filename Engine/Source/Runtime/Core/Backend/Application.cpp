#include <Core/Common/Required.h>
#include "Application.h"

#include <GLFW/glfw3.h>

using Core::Backend::Application;
using Core::Backend::AppConfigData;

/*
 *
 * name: Application::Application
 *
 * Inits SDL and its subsystems for use in other systems.
 *
 */
Application::Application (const AppConfigData & config)
: config(config)
{
	if(!glfwInit())
	{
		FATAL("GLFW failed to initialize");
	}
	DEBUG("Starting application");
}

/*
 *
 * name: Application::~Application
 *
 * Destroys SDL.  Should be one of the last things
 * done in any codebase using an Application instance.
 *
 */
Application::~Application ()
{
	Destroy();
}

void Application::Destroy ()
{
	running = false;
	glfwTerminate();
	DEBUG("Destroying application");
}
