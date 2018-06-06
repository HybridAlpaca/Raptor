#include <Core/Common/Required.h>
#include "Application.h"

#include <SDL2/SDL.h>

using Core::Backend::Application;

/*
 * 
 * name: Application::Application
 * 
 * Inits SDL and its subsystems for use in other systems.
 * 
 */
Application::Application ()
: running(true)
{
	const uint32 flags
		= SDL_INIT_AUDIO
		| SDL_INIT_VIDEO
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
	DEBUG("Created application");
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
	DEBUG("Destroying application");
	SDL_Quit();
}
