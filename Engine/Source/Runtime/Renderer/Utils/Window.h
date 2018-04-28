#pragma once

#include <Core/Misc/CoreTypes.h>

class GLFWwindow {};

/**

@class	Window
@desc	RAII Window class that uses GLFW
		to manage displays and events.

**/

class Window {

	GLFWwindow * window = nullptr;

public:

	Window (uint16 width, uint16 height, const char * title);
	
	~Window ();
	
	// methods
	
	void Close ();
	
	void Update ();
	
	// getters & setters
	
	bool shouldClose ();

};