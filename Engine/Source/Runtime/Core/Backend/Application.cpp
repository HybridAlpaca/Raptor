#include <Core/Common/Required.h>
#include "Application.h"

using Core::Backend::Application;

Application::Application ()
: running(true)
{
	const uint32 flags
		= SDL_INIT_VIDEO
		| SDL_INIT_AUDIO
		| SDL_INIT_EVENTS;
		
	uint32 currentFlags = SDL_WasInit(flags);
	
	if ((currentFlags != flags) && (SDL_Init(flags) != 0))
	{
		/* 
		 * 
		 * SDL failed for some reason or another.
		 * Probably a good idea to look under the
		 * debugger and see what's up.
		 * 
		 */
		
		FATAL("Could not initialize SDL subsystems: " << SDL_GetError());
	}
}

Application::~Application ()
{
	SDL_Quit();
}
