#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Renderer
{
namespace Utils
{

/**

@class	WindowController
@desc	Handles OpenGL context creation and
		uses X to manage displays, events,
		peripheral devices, etc.

**/

class WindowController
{

	GLFWwindow * window;
	
	bool shouldClose;
	
	static void FBResizeCallback (GLFWwindow * window, uint16 width, uint16 height);

public:

	WindowController (uint16 width, uint16 height, cchar title);
	
	~WindowController ();
	
	void Destroy ();
	
	void Update ();
	
	bool ShouldClose () const { return shouldClose; }

};

}}