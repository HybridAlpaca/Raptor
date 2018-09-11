#pragma once

#include <Raptor/Required.h>

class GLFWwindow {};

namespace Graphics
{

	struct DisplayParams
	{
		cchar title = ""; ///< The text to display on top of the window, commonly the name of the app

		uint32 width = 800; ///< Window width in px.  Value of 0 indicates full width
		uint32 height = 600; ///< Window height in px.  Value of 0 indicates full height

		uint32 vsync = 1;	///< How many monitor refreshes to wait for before a buffer swap

		bool fullscreen = false;

		// OpenGL specific
		uint8 glVersionMajor = 3; ///< @todo Move this to render device
		uint8 glVersionMinor = 3; ///< @todo Move this to render device

	};

	class Display
	{
		GLFWwindow * window;

	public:

		Display (const DisplayParams & params);

		/// @note Non-copyable
		Display (const Display & copy) = delete;

		~Display ();

		/// @note Non-copyable
		Display & operator= (const Display & rhs) = delete;

		/// @return Whether the window is closed or not
		bool Closed () const;

		/// Pulls window events off the event queue for processing
		void PollEvents () const;

		/// Swaps the front and back buffer for double buffered drawing
		void SwapBuffers () const;

		/// @return A double-precision timestamp since the window was created
		double Time () const;

		/// @return Width of the window's internal framebuffer
		uint32 FrameWidth () const;

		/// @return Height of the window's internal framebuffer
		uint32 FrameHeight () const;
	};

}
