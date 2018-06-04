#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Graphics::Utils
{

/**

@class	WindowController
@desc	Handles OpenGL context creation and
		uses X to manage displays, events,
		peripheral devices, etc.

**/

class WindowController
{

	static void FBResizeCallback (GLFWwindow * window, int16 width, int16 height);

	GLFWwindow * window;
	
	bool shouldClose;
	
	void ProcessInput ();

public:

	WindowController (uint16 width, uint16 height, cchar title);
	
	~WindowController ();
	
	void Destroy ();
	
	void Update ();
	
	bool ShouldClose () const { return shouldClose; }

};

}