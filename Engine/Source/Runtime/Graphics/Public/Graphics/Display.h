#pragma once

#include <Core/Common/Required.h>

class GLFWwindow {};

namespace Graphics
{

	struct DisplayParams
	{
		cchar title = ""; ///< The text to display on top of the window, commonly the name of the app

		uint32 width = 800; ///< Starting width in pixels of the window
		uint32 height = 600; ///< Starting height in pixels of the window

		// OpenGL specific
		uint8 glVersionMajor = 3; ///< @todo Move this to render device
		uint8 glVersionMinor = 3; ///< @todo Move this to render device

		uint32 vsync = 1;	///< How many monitor refreshes to wait for before a buffer swap
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

		/// @brief Pulls window events off the event queue for processing
		void PollEvents () const;

		/// @brief Swaps the front and back buffer for double buffered drawing
		void SwapBuffers () const;

		/// @return Width of the window's internal framebuffer
		uint32 FrameWidth () const;

		/// @return Height of the window's internal framebuffer
		uint32 FrameHeight () const;
	};

}
