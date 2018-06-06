#include <Core/Common/Required.h>
#include "Application.h"
#include "InputHandler.h"

#include <SDL2/SDL.h>

using Core::Backend::InputHandler;

InputHandler::InputHandler (Application & app)
: app(app)
{
	// TODO: Something.  Anything, really.
};

InputHandler::~InputHandler ()
{
	// TODO: Anything.  Something at all.
}

/*
 * 
 * name: InputHandler::Update
 * @return void
 * 
 * Handles event inputs from everywhere in the system.
 * This might pose a problem; as most events come from
 * the game window (in Graphics::Display).  This could
 * result in tight system coupling, which is especially
 * a problem when multithreading engine systems.
 * 
 */
void InputHandler::Update ()
{
	SDL_Event e;
	
	while (SDL_PollEvent(& e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				app.running = false;
				break;
			case SDL_KEYDOWN:
				if ((e.key.keysym.sym == SDLK_ESCAPE) || (e.key.keysym.sym == SDLK_q))
				{
					app.running = false;
				}
				break;
			default:
				break;
		}
	}
}
