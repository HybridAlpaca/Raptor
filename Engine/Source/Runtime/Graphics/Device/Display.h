#pragma once

#include <Core/Common/Required.h>
#include <SDL2/SDL.h>

class SDL_Window {};

namespace Graphics::Device
{

class Display
{
	SDL_Window * window = nullptr;
	SDL_GLContext context;
	
	bool closed = false;

public:

	Display (uint16 width, uint16 height, cchar title);
	Display (const Display & copy) = delete;
	~Display ();
	
	Display & operator= (const Display & rhs) = delete;

	void Clear (float r, float g, float b, float a);
	void Update ();
	
	const bool Closed () const { return closed; }

};

}