#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <iostream>

int main(int argc, char ** argv)
{
	Display * display;
	Window window;
	Screen * screen;
	int screenId;
	XEvent ev;

	// Open the display
	display = XOpenDisplay(NULL);
	
	if (display == NULL)
	{
		std::cout << "Could not open X display" << "\n";
		return 1;
	}
	
	screen = DefaultScreenOfDisplay(display);
	screenId = DefaultScreen(display);

	// Open the window
	window = XCreateSimpleWindow(
		display,
		RootWindowOfScreen(screen),
		0,
		0,
		320,
		200,
		1,
		BlackPixel(display, screenId),
		WhitePixel(display, screenId)
	);

	XSelectInput(display, window, KeyPressMask | KeyReleaseMask | KeymapStateMask);

	// Show the window
	XClearWindow(display, window);
	XMapRaised(display, window);
	
	Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
    XSetWMProtocols(display, window, & WM_DELETE_WINDOW, 1);
	
	// Variables used in message loop
	char str[25] = {0}; 
	KeySym keysym = 0;
	int len = 0;
	bool running = true;

	// Enter message loop
	while (running)
	{
		XNextEvent(display, &ev);
		
		switch(ev.type)
		{
			case KeymapNotify:
				XRefreshKeyboardMapping(& ev.xmapping);
			break;
			
			case KeyPress:
				len = XLookupString(& ev.xkey, str, 25, & keysym, NULL);
				if (len > 0)
					std::cout << "Key pressed: " << str << " - " << len << " - " << keysym << '\n';
				if (keysym == XK_Escape)
					running = false;
			break;
			
			case KeyRelease:
				len = XLookupString(& ev.xkey, str, 25, & keysym, NULL);
				if (len > 0)
					std::cout << "Key released: " << str << " - " << len << " - " << keysym << '\n';
			break;
			
			case ClientMessage:
				// TODO
			break;
		}
	}

	// Cleanup
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	
	return 0;
}