#include <Core/Common/Required.h>
#include "Application.h"
#include "InputHandler.h"

#include <SDL2/SDL.h>

using Core::Backend::InputHandler;
using Core::Backend::Application;

void InputHandler::KeyDown (bool & running, uint32 keyCode)
{
	switch (keyCode)
	{
		case SDLK_q:
		case SDLK_ESCAPE:
			running = false;
			break;
		default:
			DEBUG("Unknown key pressed");
			break;
	}
}
