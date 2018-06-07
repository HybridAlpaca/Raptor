#pragma once

#include "InputHandler.h"

namespace Core::Backend
{

/*
 *
 * name: Application
 * @depends SDL2
 *
 * Manages SDL subsystems for use in other
 * engine systems, i.e. Graphics::Display.
 *
 */
struct Application
{

	bool running;

	Application ();
	Application (const Application & copy) = delete;
	~Application ();

	Application & operator= (const Application & rhs) = delete;

	void HandleInput (InputHandler & input);

};

}
