#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "Window.h"

#include <Core/Misc/Required.h>

using Renderer::Utils::WindowController;

WindowController::WindowController (uint16 width, uint16 height, cchar title)
{
	if (!Init())
	{
		// failed to initialize
		return;
	}
	if (!CreateFrameBuffers())
	{
		// failed to allocate FBO's
		return;
	}
	CreateColorMap();
	CreateWindow(width, height, title);
	CreateContext();
}

WindowController::~WindowController ()
{
	Destroy();
}

void WindowController::CreateColorMap ()
{
	setAttribs.colormap
		= colormap
		= XCreateColormap(
			display,
			RootWindow(display, visualInfo -> screen),
			visualInfo -> visual,
			AllocNone
		);
		
	setAttribs.background_pixmap = None;
	setAttribs.border_pixel = 0;
	setAttribs.event_mask = StructureNotifyMask;
}

bool WindowController::CreateContext ()
{
	cchar glExts = glXQueryExtensionsString(
		display,
		DefaultScreen(display)
	);
	
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
		(glXCreateContextAttribsARBProc)
		glXGetProcAddressARB((const GLubyte *) "glXCreateContextAttribsARB");
		
	return true;
}

bool WindowController::CreateFrameBuffers ()
{
	int16 fbCount;
	GLXFBConfig * fbc = glXChooseFBConfig(
		display,
		DefaultScreen(display),
		visualAttribs,
		& fbCount
	);
	
	if (!fbc)
	{
		// failed to retrieve a framebuffer config
		return false;
	}
	
	int16
		bestFbc = -1,
		worstFbc = -1,
		bestNumSamples = -1,
		worstNumSamples = 999;
		
	for (int8 i = 0; i < fbCount; i++)
	{
		visualInfo = glXGetVisualFromFBConfig(display, fbc[i]);
		if (visualInfo)
		{
			int16 sampleBuffer, samples;
			glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS, & sampleBuffer);
			glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, & samples);
			
			if (bestFbc < 0 || sampleBuffer && samples > bestNumSamples)
			{
				bestFbc = i;
				bestNumSamples = samples;
			}
			if (worstFbc  < 0 || !sampleBuffer || samples < worstNumSamples)
			{
				worstFbc = i;
				worstNumSamples = samples;
			}
		}
		XFree(visualInfo);
		visualInfo = nullptr;
	}
	
	GLXFBConfig FBC = fbc[bestFbc];
	
	// we don't need this list anymore
	XFree(fbc);
	
	visualInfo = glXGetVisualFromFBConfig(display, FBC);
	
	// int16 visualID = visualInfo -> visualid
	
	return true;
}

bool WindowController::CreateWindow (uint16 & width, uint16 & height, cchar title)
{
	window = XCreateWindow(
		display,
		RootWindow(display, visualInfo -> screen),
		0,
		0,
		width,
		height,
		0,
		visualInfo -> depth,
		InputOutput,
		visualInfo -> visual,
		CWBorderPixel | CWColormap | CWEventMask,
		& setAttribs
	);
	
	if (!window)
	{
		// window creation failed
		return false;
	}
	
	XFree(visualInfo);
	XStoreName(display, window, title);
	XMapWindow(display, window);
	
	return true;
}

bool WindowController::ExtensionSupported (cchar extension_list, cchar extension)
{
	//
}

void WindowController::Destroy ()
{
	//
}

bool WindowController::Init ()
{
	display = XOpenDisplay(nullptr);
	
	if (!display)
	{
		// If the display returned NULL,
		// indicate that creation failed.
		return false;
	}
	
	if (!glXQueryVersion(display, & glxMajor, &glxMinor) || 
		((glxMajor == 1) && (glxMinor < 3)) || (glxMajor < 1))
	{
		// An invalid GLX version was provided,
		// not our problem to sort out.
		return false;
	}
	
	return true;
}