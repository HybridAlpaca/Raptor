#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include "Window.h"

#include <Core/Misc/CoreTypes.h>

using Renderer::Utils::WindowController;

WindowController::WindowController (uint16 width, uint16 height, const char * title)
{
	display = XOpenDisplay(nullptr);
	
	if (display == nullptr)
	{
		// Failed to connect to X11 Server
		return;	
	}
	
	root = DefaultRootWindow(display);

	visualInfo = glXChooseVisual(display, 0, attributes);

	if (visualInfo == nullptr)
	{
		// No appropriate visual found
		return;
	}
	// selected visual ID == (void *) vi -> visualid
	
	colorMap = XCreateColormap(display, root, visualInfo -> visual, AllocNone);

	setAttributes.colormap = colorMap;
	setAttributes.event_mask = ExposureMask | KeyPressMask;

	window = XCreateWindow(
		display,
		root,
		0,
		0,
		width,
		height,
		0,
		visualInfo -> depth,
		InputOutput,
		visualInfo -> visual,
		CWColormap | CWEventMask,
		& setAttributes
	);

	XMapWindow(display, window);
	XStoreName(display, window, title);

	context = glXCreateContext(display, visualInfo, nullptr, GL_TRUE);
	glXMakeCurrent(display, window, context);
}

WindowController::~WindowController ()
{
	Destroy();
}

void WindowController::Destroy ()
{
	glXMakeCurrent(display, None, nullptr);
	glXDestroyContext(display, context);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

void WindowController::Update ()
{
	XNextEvent(display, & event);
}