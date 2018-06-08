#include <Core/Common/Required.h>
#include "Application.h"
#include "InputHandler.h"

#include <GLFW/glfw3.h>

using Core::Backend::InputHandler;
using Core::Backend::Application;

void InputHandler::Process (Application & app)
{
	glfwPollEvents();
}
