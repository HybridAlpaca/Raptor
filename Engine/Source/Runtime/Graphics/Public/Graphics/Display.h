#pragma once

#include <Raptor/Required.h>

namespace Graphics::Display
{

	using WindowHandle = uint16;

	static const WindowHandle NULL_HANDLE = 0;

	static const uint16 MAX_WINDOWS = 65535;

	struct InitDescriptor
	{
		cchar title = ""; ///< The text to display on top of the window, commonly the name of the app

		uint32 width  = 800; ///< Window width in px.  Value of 0 indicates full width
		uint32 height = 600; ///< Window height in px.  Value of 0 indicates full height

		uint32 vsync = 1;	///< How many monitor refreshes to wait for before a buffer swap

		bool fullscreen = false;

		// OpenGL specific

		uint8 glVersionMajor = 3; ///< @todo Move this to render device
		uint8 glVersionMinor = 3; ///< @todo Move this to render device

	};

	WindowHandle Create (const InitDescriptor & desc);

	void Destroy (WindowHandle window);

	bool Closed (WindowHandle window);

	void Close (WindowHandle window);

	void PollEvents ();

	void SwapBuffers (WindowHandle window);

	/// @warning Temporary.
	uint32 FrameWidth (WindowHandle window);

	/// @warning Temporary.
	uint32 FrameHeight (WindowHandle window);

}
