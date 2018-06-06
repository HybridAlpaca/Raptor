#pragma once

#include <Core/Common/Required.h>
#include <SDL2/SDL.h>

namespace Graphics::Device
{

/*
 * 
 * name: Display
 * 
 * @depends Core, SDL2
 * 
 */
class Display
{
	Core::Backend::Application & app;
	
	SDL_Window * window = nullptr;
	SDL_GLContext context;

public:

	Display (Core::Backend::Application & application, uint16 width, uint16 height, cchar title);
	Display (const Display & copy) = delete;
	~Display ();

	Display & operator= (const Display & rhs) = delete;

	void Clear (float r, float g, float b, float a);
	void Update ();
};

}
