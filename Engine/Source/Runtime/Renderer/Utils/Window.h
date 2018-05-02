#pragma once

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <Core/Misc/CoreTypes.h>

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

	Colormap colorMap;
	Display * display;

	GLXContext context;

	Window root;
	Window window;

	XEvent event;
	XSetWindowAttributes setAttributes;
	XVisualInfo * visualInfo;
	XWindowAttributes getAttributes;

	int16 attributes[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

public:

	WindowController (uint16 width, uint16 height, const char * title);
	
	~WindowController ();
	
	void Destroy ();
	
	void Update ();

};

}}