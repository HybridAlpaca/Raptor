#pragma once

namespace Core::Backend
{

/*
 * 
 * name: Application
 * 
 * @depends Core, SDL2
 * 
 * Instantiates SDL with predefined subsystems.
 * Does nothing on its own, but prepares other
 * engine systems (i.e. Graphics::Display) for
 * use.
 * 
 */
class Application
{
	bool running;

public:

	Application ();
	Application (const Application & copy) = delete;
	~Application ();
	
	Application & operator= (const Application & rhs) = delete;
	
	const bool Running () const { return running; }
	void Running (bool shouldRun) { running = shouldRun; }
};

}
