#pragma once

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <Core/Misc/Required.h>

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

	static const int16 GLX_VERSION_MAJOR_ARB = 0x2091;
	static const int16 GLX_VERSION_MINOR_ARB = 0x2092;

	static bool glxError;
	
	static int8 glxErrorHandler ();

	Colormap colormap;
	Display * display;
	Window window;
	
	XSetWindowAttributes setAttribs;
	XVisualInfo * visualInfo;
	
	int16
		glxMajor,
		glxMinor;
		
	int16 visualAttribs [23] =
	{
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		//GLX_SAMPLE_BUFFERS  , 1,
		//GLX_SAMPLES         , 4,
		None
	};

	void CreateColorMap ();

	bool CreateContext ();
	
	bool CreateFrameBuffers ();
	
	bool CreateWindow (uint16 & width, uint16 & height);

	bool ExtensionSupported (cchar extension_list, cchar extension);
	
	bool Init ();

public:

	WindowController (uint16 width, uint16 height, cchar title);
	
	~WindowController ();
	
	void Destroy ();

};

}}