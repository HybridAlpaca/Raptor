#pragma once

namespace Core::Backend
{

/*
 * 
 * name: Application
 * @depends SDL2
 * 
 * Manages SDL subsystems for use in other
 * engine systems.  Doesn't do much by itself;
 * but is required for other systems to work.
 * (i.e. Graphics::Display, etc.)
 * 
 */
struct Application
{
	bool running;
	
	Application ();
	Application (const Application & copy) = delete;
	~Application ();
	
	Application & operator= (const Application & rhs) = delete;
};

}
