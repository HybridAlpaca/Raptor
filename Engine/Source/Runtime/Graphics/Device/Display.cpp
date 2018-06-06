#include <Core/Common/Required.h>
#include "Display.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

using Graphics::Device::Display;

/*
 * 
 * name: Display::Display
 * @param uint16 width, height; cchar title
 * 
 * Handles creation of SDL window and OpenGL
 * context.
 * 
 */
Display::Display (uint16 width, uint16 height, cchar title)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	
	context = SDL_GL_CreateContext(window);
	
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
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
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

/*
 * 
 * name: Display::Update
 * @param void
 * @return void
 * 
 * Updates the display, to be called after
 * any other draw operations are performed.
 * 
 * TODO: Move event code into Core::Application
 * 
 */
void Display::Update ()
{
	SDL_GL_SwapWindow(window);
	
	SDL_Event e;
	
	while (SDL_PollEvent(& e))
	{
		if (e.type == SDL_QUIT)
			closed = true;
		if (e.type == SDL_KEYDOWN)
		{
			if ((e.key.keysym.sym == SDLK_ESCAPE) || (e.key.keysym.sym == SDLK_q))
			{
				closed = true;
			}
		}
	}
}





