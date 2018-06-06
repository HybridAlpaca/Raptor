#pragma once

#include <Core/Common/Required.h>

namespace Core::Backend
{

class Application;

/*
 * 
 * name: InputHandler
 * @depends SDL2
 * 
 * Keeps track of inputs from the OS via SDL
 * and operates on them directly.
 * 
 * TODO: Tie this to a global event system
 * 
 */
 
class InputHandler
{
	Application & app;
	
public:

	InputHandler (Application & app);
	InputHandler (const InputHandler & copy) = delete;
	~InputHandler ();
	
	InputHandler & operator= (const InputHandler & rhs) = delete;
	
	void Update ();
};
	
}
