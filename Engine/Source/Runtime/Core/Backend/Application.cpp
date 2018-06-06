#include <Core/Common/Required.h>
#include "Application.h"

using Core::Backend::Application;

Application::Application ()
: running(true)
{
	const uint32 flags
		= SDL_INIT_VIDEO
		| SDL_INIT_EVENTS;
		
	uint32 currentFlags = SDL_WasInit(flags);
	if ((currentFlags != flags) && (SDL_Init(flags) != 0))
	{
		DEBUG("Could not initialize SDL subsystems: " << SDL_GetError());
	}
}

Application::~Application ()
{
	SDL_Quit();
}
