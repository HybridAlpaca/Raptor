#pragma once

namespace Core::Backend
{

class Application
{
	bool running;

public:

	Application ();
	Application (const Application & copy) = delete;
	~Application ();
	
	Application & operator= (const Application & rhs) = delete;
	
	void ProcessInput (const InputHandler & handler);
	
	const bool Running () const { return running; }
	void Running (bool shouldRun) { running = shouldRun; }
};

}
